#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */

volatile unsigned char loop;
volatile unsigned char LEDs[54];
volatile unsigned char SortLEDs[54];
volatile unsigned char POS;

#define pLedDi			PORTA,2
#define kNumberOfLed	18

//PORTA bank0縲?LATA bank2
volatile uint8_t	dt		@ 0x20;
volatile uint8_t	bitCount @ 0x21;
volatile uint8_t	byteCount @ 0x22;
volatile uint16_t	saveFsr	@ 0x23;


#define setID 6
unsigned char myID = (setID - 1);

#define UART_BUFFER_SIZE   64
unsigned char UART_Buffer[UART_BUFFER_SIZE]; // 受信したデータを格納するバッファ
unsigned char UART_Buffer_inptr;
unsigned char UART_Buffer_outptr;

unsigned char UART_Read();
int UART_Available();
void InitUART(int rx, int tx, char brg);

void Set_LEDs_16(void);
void Set_Color(void);
//#define Z 2
//#define C 0
//#define W 0
//#define F 1

//void Set_LEDs_16(void) {
//    //    GIE = 0;
//#asm
//    MOVLW 0x50;
//    MOVWF FSR0L;
//    MOVLW 0x20;
//    MOVWF FSR0H; // FSR0を0x2000に
//
//    CLRF _POS; // POS=0;
//    CLRF FSR1L;
//    CLRF FSR1H;
//
//    BANKSEL _loop;
//    MOVLW 54;
//    MOVWF _loop; //loop=3;
//
//_GET_DATA:
//    MOVLW _SortLEDs; //W=LEDs
//    ADDWF _POS, W; //W=W+POS
//    MOVWF FSR1L;
//    MOVF INDF1, W;
//    MOVWF INDF0; //FSR0にWを
//    INCF FSR0L, F; //FSR0を次のアドレスに
//
//    INCF _POS, F; //pos=pos+1;
//
//    DECF _loop, F; //loop=loop-1;
//    BTFSS STATUS, 2;
//    GOTO _GET_DATA;
//
//
//    //ここからWS2812と通信
//    BANKSEL _loop;
//    MOVLW 54;
//    MOVWF _loop; //ループする回数
//
//    MOVLW 0x50;
//    MOVWF FSR0L;
//    MOVLW 0x20;
//    MOVWF FSR0H;
//
//    // 7bit
//_SET_7:
//    BANKSEL PORTA;
//    BCF PORTA, 2; //Bit=0;
//
//_NEXT_7:
//    NOP; //1:NOP
//    MOVF INDF0, W; //2:Wから読み込み
//
//    BANKSEL PORTA; //3:Bit=1;
//    BSF PORTA, 2; //4:
//    BTFSC WREG, 7; //5:Wの7bitが0なら次をスキップ
//    GOTO _SET_0_G_7; //6:
//    BCF PORTA, 2; //7:Bit=0;
//    GOTO _NEXT_0_G_7; //8:
//_SET_0_G_7:
//    NOP; //9:
//    BCF PORTA, 2; //10:
//
//_NEXT_0_G_7:
//    // 6bit
//    NOP;
//    INCF FSR0L, F;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 6;
//    GOTO _SET_0_G_6;
//    BCF PORTA, 2;
//    GOTO _NEXT_0_G_6;
//_SET_0_G_6:
//    NOP;
//    BCF PORTA, 2;
//
//_NEXT_0_G_6:
//    // 5bit
//    NOP;
//    NOP;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 5;
//    GOTO _SET_0_G_5;
//    BCF PORTA, 2;
//    GOTO _NEXT_0_G_5;
//_SET_0_G_5:
//    NOP;
//    BCF PORTA, 2;
//
//_NEXT_0_G_5:
//    // 4bit
//    NOP;
//    NOP;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 4;
//    GOTO _SET_0_G_4;
//    BCF PORTA, 2;
//    GOTO _NEXT_0_G_4;
//_SET_0_G_4:
//    NOP;
//    BCF PORTA, 2;
//
//_NEXT_0_G_4:
//    // 3bit
//    NOP;
//    NOP;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 3;
//    GOTO _SET_0_G_3;
//    BCF PORTA, 2;
//    GOTO _NEXT_0_G_3;
//_SET_0_G_3:
//    NOP;
//    BCF PORTA, 2;
//
//_NEXT_0_G_3:
//    // 2bit
//    NOP;
//    NOP;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 2;
//    GOTO _SET_0_G_2;
//    BCF PORTA, 2;
//    GOTO _NEXT_0_G_2;
//_SET_0_G_2:
//    NOP;
//    BCF PORTA, 2;
//
//_NEXT_0_G_2:
//    // 1bit
//    NOP;
//    DECF _loop, f;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 1;
//    GOTO _SET_0_G_1;
//    BCF PORTA, 2;
//    GOTO _NEXT_0_G_1;
//_SET_0_G_1:
//    NOP;
//    BCF PORTA, 2;
//
//_NEXT_0_G_1:
//    // 0bit
//    BTFSC STATUS, 2;
//    GOTO _LOOP_END;
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 0;
//    GOTO _SET_7;
//    BCF PORTA, 2;
//    GOTO _NEXT_7;
//
//_LOOP_END:
//    BANKSEL PORTA;
//    BSF PORTA, 2;
//    BTFSC WREG, 0;
//    GOTO _SET;
//    BCF PORTA, 2;
//    GOTO _NEXT;
//_SET:
//    NOP;
//    BCF PORTA, 2;
//_NEXT:
//#endasm
//
//    // reset period
//    __delay_us(50);
//
//}
void Set_LEDs_16( void )
{
	//go
	//di();
#asm
	banksel	_byteCount
	movf	FSR0L, W
	movwf	_saveFsr
	movf	FSR0H, W
	movwf	_saveFsr+1			;save FSR0

	movlw	(kNumberOfLed*3)
	movwf	_byteCount
	movlw	low(_SortLEDs)			;top address
	movwf	FSR0L
	movlw	high(_SortLEDs)
	movwf	FSR0H
	clrf	_bitCount
	goto	ByteLoop

Adjust:
	nop						; 1
	rlf		_dt, F			; 1
	goto	BitLoop			; 2

ByteLoop:
	moviw	FSR0++			; 1
	movwf	_dt				; 1
	bsf		_bitCount, 3	; 1  set 8
BitLoop:
	bsf		pLedDi			; 1
	btfsc	_dt, 7			; 1
	goto	Send1			; 2 or 1
	bcf		pLedDi			; 1			375nS
	decfsz	_bitCount, F	; 1
	goto	Adjust			; 2
	decfsz	_byteCount, F	; 1
	goto	ByteLoop		; 2
	goto	SendEnd
Send1:
	rlf		_dt, F			; 1
	nop						; 1
	nop						; 1
	bcf		pLedDi			; 1			875nS
	decfsz	_bitCount, F	; 1
	goto	BitLoop			; 2
	decfsz	_byteCount, F	; 1
	goto	ByteLoop		; 2
SendEnd:
	movf	_saveFsr, W
	movwf	FSR0L
	movf	_saveFsr+1, W
	movwf	FSR0H
#endasm
	//ei();
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

    //InitUART(2, 3, 32); //250000
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
                if (dataPos >= (myID * 18) && dataPos < (myID + 1)*18) {
                    LEDs[dataPos - (myID * 18)] = RcvData;
                }
                dataPos++;
            }
        }

        if (dataPos - (myID * 18) == 17) {
            if (receiveMyID == 1) {

                Set_Color();
                receiveMyID = 0;
            }
        }

    }
}

void Set_Color() {

    SortLEDs[0] = LEDs[0];
    SortLEDs[1] = LEDs[1];
    SortLEDs[2] = LEDs[2];
    SortLEDs[3] = LEDs[0];
    SortLEDs[4] = LEDs[1];
    SortLEDs[5] = LEDs[2];
    SortLEDs[6] = LEDs[0];
    SortLEDs[7] = LEDs[1];
    SortLEDs[8] = LEDs[2];

    SortLEDs[9] = LEDs[3];
    SortLEDs[10] = LEDs[4];
    SortLEDs[11] = LEDs[5];
    SortLEDs[12] = LEDs[3];
    SortLEDs[13] = LEDs[4];
    SortLEDs[14] = LEDs[5];
    SortLEDs[15] = LEDs[3];
    SortLEDs[16] = LEDs[4];
    SortLEDs[17] = LEDs[5];

    SortLEDs[18] = LEDs[6];
    SortLEDs[19] = LEDs[7];
    SortLEDs[20] = LEDs[8];
    SortLEDs[21] = LEDs[6];
    SortLEDs[22] = LEDs[7];
    SortLEDs[23] = LEDs[8];
    SortLEDs[24] = LEDs[6];
    SortLEDs[25] = LEDs[7];
    SortLEDs[26] = LEDs[8];

    SortLEDs[27] = LEDs[15];
    SortLEDs[28] = LEDs[16];
    SortLEDs[29] = LEDs[17];
    SortLEDs[30] = LEDs[15];
    SortLEDs[31] = LEDs[16];
    SortLEDs[32] = LEDs[17];
    SortLEDs[33] = LEDs[15];
    SortLEDs[34] = LEDs[16];
    SortLEDs[35] = LEDs[17];

    SortLEDs[36] = LEDs[12];
    SortLEDs[37] = LEDs[13];
    SortLEDs[38] = LEDs[14];
    SortLEDs[39] = LEDs[12];
    SortLEDs[40] = LEDs[13];
    SortLEDs[41] = LEDs[14];
    SortLEDs[42] = LEDs[12];
    SortLEDs[43] = LEDs[13];
    SortLEDs[44] = LEDs[14];

    SortLEDs[45] = LEDs[9];
    SortLEDs[46] = LEDs[10];
    SortLEDs[47] = LEDs[11];
    SortLEDs[48] = LEDs[9];
    SortLEDs[49] = LEDs[10];
    SortLEDs[50] = LEDs[11];
    SortLEDs[51] = LEDs[9];
    SortLEDs[52] = LEDs[10];
    SortLEDs[53] = LEDs[11];

    GIE = 0;
    Set_LEDs_16();
    GIE = 1;
}

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

    BAUDCONbits.BRG16 = 0;

    SPBRG = brg; // ボーレートの設定

    RCIF = 0; // USART割込み受信フラグの初期化
    RCIE = 1; // USART割込み受信を有効にする
    PEIE = 1; // 周辺装置割込みを有効にする

    GIE = 1; // 全割込み処理を許可する

    UART_Buffer_inptr = 0; // 受信バッファの読み込みポインターの初期化
    UART_Buffer_outptr = 0; // 受信バッファの書き込みポインターの初期化
}




