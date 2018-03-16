#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */

volatile unsigned char loop;
volatile unsigned char LEDs[54];
volatile unsigned char POS;

#define setID 1
unsigned char myID = (setID-1);

#define UART_BUFFER_SIZE   128
unsigned char UART_Buffer[UART_BUFFER_SIZE]; // ��M�����f�[�^���i�[����o�b�t�@
unsigned char UART_Buffer_inptr;
unsigned char UART_Buffer_outptr;

unsigned char UART_Read();
int UART_Available();
void InitUART(int rx, int tx, char brg);

void Set_LEDs_16(void);

//#define Z 2
//#define C 0
//#define W 0
//#define F 1

void Set_LEDs_16(void) {
    //    GIE = 0;
#asm
    MOVLW 0x50;
    MOVWF FSR0L;
    MOVLW 0x20;
    MOVWF FSR0H; // FSR0��0x2000��

    CLRF _POS; // POS=0;
    CLRF FSR1L;
    CLRF FSR1H;

    BANKSEL _loop;
    MOVLW 54;
    MOVWF _loop; //loop=3;

_GET_DATA:
    MOVLW _LEDs; //W=LEDs
    ADDWF _POS, W; //W=W+POS
    MOVWF FSR1L;
    MOVF INDF1, W;
    MOVWF INDF0; //FSR0��W��
    INCF FSR0L, F; //FSR0�����̃A�h���X��

    INCF _POS, F; //pos=pos+1;

    DECF _loop, F; //loop=loop-1;
    BTFSS STATUS, 2;
    GOTO _GET_DATA;


    //��������WS2812�ƒʐM
    BANKSEL _loop;
    MOVLW 54;
    MOVWF _loop; //���[�v�����

    MOVLW 0x50;
    MOVWF FSR0L;
    MOVLW 0x20;
    MOVWF FSR0H;

    // 7bit
_SET_7:
    BANKSEL PORTA;
    BCF PORTA, 2; //Bit=0;

_NEXT_7:
    NOP; //1:NOP
    MOVF INDF0, W; //2:W����ǂݍ���

    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 7; //5:W��7bit��0�Ȃ玟���X�L�b�v
    GOTO _SET_0_G_7; //6:
    BCF PORTA, 2; //7:Bit=0;
    GOTO _NEXT_0_G_7; //8:
_SET_0_G_7:
    NOP; //9:
    BCF PORTA, 2; //10:

_NEXT_0_G_7:
    // 6bit
    NOP;
    INCF FSR0L, F;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 6;
    GOTO _SET_0_G_6;
    BCF PORTA, 2;
    GOTO _NEXT_0_G_6;
_SET_0_G_6:
    NOP;
    BCF PORTA, 2;

_NEXT_0_G_6:
    // 5bit
    NOP;
    NOP;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 5;
    GOTO _SET_0_G_5;
    BCF PORTA, 2;
    GOTO _NEXT_0_G_5;
_SET_0_G_5:
    NOP;
    BCF PORTA, 2;

_NEXT_0_G_5:
    // 4bit
    NOP;
    NOP;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 4;
    GOTO _SET_0_G_4;
    BCF PORTA, 2;
    GOTO _NEXT_0_G_4;
_SET_0_G_4:
    NOP;
    BCF PORTA, 2;

_NEXT_0_G_4:
    // 3bit
    NOP;
    NOP;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 3;
    GOTO _SET_0_G_3;
    BCF PORTA, 2;
    GOTO _NEXT_0_G_3;
_SET_0_G_3:
    NOP;
    BCF PORTA, 2;

_NEXT_0_G_3:
    // 2bit
    NOP;
    NOP;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 2;
    GOTO _SET_0_G_2;
    BCF PORTA, 2;
    GOTO _NEXT_0_G_2;
_SET_0_G_2:
    NOP;
    BCF PORTA, 2;

_NEXT_0_G_2:
    // 1bit
    NOP;
    DECF _loop, f;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 1;
    GOTO _SET_0_G_1;
    BCF PORTA, 2;
    GOTO _NEXT_0_G_1;
_SET_0_G_1:
    NOP;
    BCF PORTA, 2;

_NEXT_0_G_1:
    // 0bit
    BTFSC STATUS, 2;
    GOTO _LOOP_END;
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 0;
    GOTO _SET_7;
    BCF PORTA, 2;
    GOTO _NEXT_7;

_LOOP_END:
    BANKSEL PORTA;
    BSF PORTA, 2;
    BTFSC WREG, 0;
    GOTO _SET;
    BCF PORTA, 2;
    GOTO _NEXT;
_SET:
    NOP;
    BCF PORTA, 2;
_NEXT:
#endasm

    // reset period
    __delay_us(50);

}


unsigned char RcvData;
unsigned int dataPos;
unsigned char receiveMyID;

void main(void) {

    ConfigureOscillator();
    __delay_ms(100);
    

    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA5 = 1; //RX

    LATAbits.LATA2 = 0;

    InitUART(2, 3, 16); //115200
    //InitUART(2, 3, 34); //57600
    //InitUART(2, 3, 103); //19200
    //InitUART(2, 3, 207);//9600


    while (1) {
        if (UART_Available() > 0) {
            RcvData = UART_Read();

            if (RcvData == 255) {
                dataPos = 0;
                receiveMyID = 1;
            } else {
                if (dataPos >= (myID * 54) && dataPos < (myID + 1)*54) {
                    LEDs[dataPos - (myID * 54)] = RcvData;
                }
                dataPos++;
            }
        }

        if (dataPos - (myID * 54) == 53) {
            if (receiveMyID == 1) {
                GIE = 0;
                Set_LEDs_16();
                GIE = 1;
                receiveMyID = 0;
            }
        }

    }
}

//
//void Set_Color(unsigned char R, unsigned char G, unsigned char B, char LED) {
//    LEDs[LED * 3 + 0] = G;
//    LEDs[LED * 3 + 1] = R;
//    LEDs[LED * 3 + 2] = B;
//}

/******************************
GlobalInt
 *******************************/
void interrupt isr(void) {
    //    int i;
    int x;
    unsigned char dt;

    if (RCIF == 1) { // �����݂͂t�r�`�q�s�ʐM�̎�M���H
        // ���W�X�^����f�[�^����M
        dt = RCREG;
        x = (UART_Buffer_outptr + 1) % UART_BUFFER_SIZE;
        if (x != UART_Buffer_inptr) {
            // �o�b�t�@�����t�łȂ��Ȃ�f�[�^��ۑ�����
            UART_Buffer[UART_Buffer_outptr] = dt;
            // �o�b�t�@�������݃|�C���^�[�����ɐi�߂�
            UART_Buffer_outptr = x;
        }

        // �I�[�o�����G���[����(RCREG�o�b�t�@���R�ڂ̃f�[�^����M������I�[�o�t���[)
        if (OERR == 1) {
            CREN = 0;
            while (OERR);
            CREN = 1;
        }
        // �����ݎ�M�t���O�����Z�b�g
        RCIF = 0;
    }
}

unsigned char UART_Read() {
    unsigned int ans;
    // �o�b�t�@�͋�ł���
    if (UART_Buffer_inptr == UART_Buffer_outptr) return 0xffff;
    // �o�b�t�@����ǂݏo��
    ans = UART_Buffer[UART_Buffer_inptr];
    // �o�b�t�@�ǂݍ��݃|�C���^�[�����ɐi�߂�
    UART_Buffer_inptr = (UART_Buffer_inptr + 1) % UART_BUFFER_SIZE;

    return ans;
}

int UART_Available() {
    return (UART_Buffer_outptr + UART_BUFFER_SIZE - UART_Buffer_inptr) % UART_BUFFER_SIZE;
}

void InitUART(int rx, int tx, char brg) {
    RXDTSEL = 0; // 6�ԃs��(RA1)��RX��M�s���Ƃ���
    TXCKSEL = 0; // 7�ԃs��(RA0)��TX���M�s���Ƃ���
    if (rx == 2) RXDTSEL = 1; // 2�ԃs��(RA5)��RX��M�s���Ƃ���
    if (tx == 3) TXCKSEL = 1; // 3�ԃs��(RA4)��TX��M�s���Ƃ���


    TXSTA = 0b00000100; // �񓯊����[�h�@�W�r�b�g�E�m���p���e�B
    RCSTA = 0b10010000; // ��M���ݒ�

    SPBRG = brg; // �{�[���[�g�̐ݒ�

    RCIF = 0; // USART�����ݎ�M�t���O�̏�����
    RCIE = 1; // USART�����ݎ�M��L���ɂ���
    PEIE = 1; // ���ӑ��u�����݂�L���ɂ���

    GIE = 1; // �S�����ݏ�����������

    UART_Buffer_inptr = 0; // ��M�o�b�t�@�̓ǂݍ��݃|�C���^�[�̏�����
    UART_Buffer_outptr = 0; // ��M�o�b�t�@�̏������݃|�C���^�[�̏�����
}




