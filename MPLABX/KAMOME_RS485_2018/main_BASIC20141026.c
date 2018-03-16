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
unsigned char UART_Buffer[UART_BUFFER_SIZE]; // 受信したデータを格納するバッファ
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
    MOVWF FSR0H; // FSR0を0x2000に

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
    MOVWF INDF0; //FSR0にWを
    INCF FSR0L, F; //FSR0を次のアドレスに

    INCF _POS, F; //pos=pos+1;

    DECF _loop, F; //loop=loop-1;
    BTFSS STATUS, 2;
    GOTO _GET_DATA;


    //ここからWS2812と通信
    BANKSEL _loop;
    MOVLW 54;
    MOVWF _loop; //ループする回数

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
    MOVF INDF0, W; //2:Wから読み込み

    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 7; //5:Wの7bitが0なら次をスキップ
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

    if (RCIF == 1) { // 割込みはＵＳＡＲＴ通信の受信か？
        // レジスタからデータを受信
        dt = RCREG;
        x = (UART_Buffer_outptr + 1) % UART_BUFFER_SIZE;
        if (x != UART_Buffer_inptr) {
            // バッファが満杯でないならデータを保存する
            UART_Buffer[UART_Buffer_outptr] = dt;
            // バッファ書き込みポインターを次に進める
            UART_Buffer_outptr = x;
        }

        // オーバランエラー処理(RCREGバッファが３個目のデータを受信したらオーバフロー)
        if (OERR == 1) {
            CREN = 0;
            while (OERR);
            CREN = 1;
        }
        // 割込み受信フラグをリセット
        RCIF = 0;
    }
}

unsigned char UART_Read() {
    unsigned int ans;
    // バッファは空である
    if (UART_Buffer_inptr == UART_Buffer_outptr) return 0xffff;
    // バッファから読み出す
    ans = UART_Buffer[UART_Buffer_inptr];
    // バッファ読み込みポインターを次に進める
    UART_Buffer_inptr = (UART_Buffer_inptr + 1) % UART_BUFFER_SIZE;

    return ans;
}

int UART_Available() {
    return (UART_Buffer_outptr + UART_BUFFER_SIZE - UART_Buffer_inptr) % UART_BUFFER_SIZE;
}

void InitUART(int rx, int tx, char brg) {
    RXDTSEL = 0; // 6番ピン(RA1)をRX受信ピンとする
    TXCKSEL = 0; // 7番ピン(RA0)をTX送信ピンとする
    if (rx == 2) RXDTSEL = 1; // 2番ピン(RA5)をRX受信ピンとする
    if (tx == 3) TXCKSEL = 1; // 3番ピン(RA4)をTX受信ピンとする


    TXSTA = 0b00000100; // 非同期モード　８ビット・ノンパリティ
    RCSTA = 0b10010000; // 受信情報設定

    SPBRG = brg; // ボーレートの設定

    RCIF = 0; // USART割込み受信フラグの初期化
    RCIE = 1; // USART割込み受信を有効にする
    PEIE = 1; // 周辺装置割込みを有効にする

    GIE = 1; // 全割込み処理を許可する

    UART_Buffer_inptr = 0; // 受信バッファの読み込みポインターの初期化
    UART_Buffer_outptr = 0; // 受信バッファの書き込みポインターの初期化
}




