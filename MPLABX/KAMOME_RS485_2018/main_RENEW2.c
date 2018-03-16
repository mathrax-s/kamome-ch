#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */


volatile unsigned char loop;

void Set_LEDs_16(void);
void Set_Color(unsigned char R, unsigned char G, unsigned char B, char LED);

volatile unsigned char LEDs[54];
volatile unsigned char POS;

//unsigned char LEDs_0_r = 0x00;
//unsigned char LEDs_0_g = 0x00;
//unsigned char LEDs_0_b = 0x00;
//unsigned char LEDs_1_r = 0x00;
//unsigned char LEDs_1_g = 0x00;
//unsigned char LEDs_1_b = 0x00;
//unsigned char LEDs_2_r = 0x00;
//unsigned char LEDs_2_g = 0x00;
//unsigned char LEDs_2_b = 0x00;
//unsigned char LEDs_3_r = 0x00;
//unsigned char LEDs_3_g = 0x00;
//unsigned char LEDs_3_b = 0x00;
//unsigned char LEDs_4_r = 0x00;
//unsigned char LEDs_4_g = 0x00;
//unsigned char LEDs_4_b = 0x00;
//unsigned char LEDs_5_r = 0x00;
//unsigned char LEDs_5_g = 0x00;
//unsigned char LEDs_5_b = 0x00;
//unsigned char LEDs_6_r = 0x00;
//unsigned char LEDs_6_g = 0x00;
//unsigned char LEDs_6_b = 0x00;
//unsigned char LEDs_7_r = 0x00;
//unsigned char LEDs_7_g = 0x00;
//unsigned char LEDs_7_b = 0x00;
//unsigned char LEDs_8_r = 0x00;
//unsigned char LEDs_8_g = 0x00;
//unsigned char LEDs_8_b = 0x00;

void Set_LEDs_16(void) {
#asm
    MOVLW 0x20;
    MOVWF FSR0L;
    MOVLW 0x20;
    MOVWF FSR0H; // FSR0を0x2000に

    CLRF _POS; // POS=0;

    MOVLW _LEDs;    //W ←_LEDsの先頭アドレス
    ADDWF _POS, W;  //_POS 分だけポインタを進める

_GET_DATA:
    MOVF _POS, W;
    MOVWF INDF0; //FSR0をWに

    INCF FSR0L, F; //FSR0を次のアドレスに
    INCF _POS, F;

    MOVF _POS, W;
    MOVWF INDF0; //FSR0をWに

    INCF FSR0L, F; //FSR0を次のアドレスに
    INCF _POS, F;

    MOVF _POS, W;
    MOVWF INDF0; //FSR0をWに

    INCF FSR0L, F; //FSR0を次のアドレスに
    INCF _POS, F;



    //    GOTO _GET_DONE; //2:???????F
    //_GET_DONE:

    //    BANKSEL _LEDs + 1;
    //    MOVF _LEDs+1, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 2;
    //    MOVF _LEDs+2, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 3;
    //    MOVF _LEDs+3, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 4;
    //    MOVF _LEDs+4, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 5;
    //    MOVF _LEDs+5, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 6;
    //    MOVF _LEDs+6, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 7;
    //    MOVF _LEDs+7, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 8;
    //    MOVF _LEDs+8, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 9;
    //    MOVF _LEDs+9, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 10;
    //    MOVF _LEDs+10, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 11;
    //    MOVF _LEDs+11, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 12;
    //    MOVF _LEDs+12, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 13;
    //    MOVF _LEDs+13, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 14;
    //    MOVF _LEDs+14, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 15;
    //    MOVF _LEDs+15, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 16;
    //    MOVF _LEDs+16, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 17;
    //    MOVF _LEDs+17, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 18;
    //    MOVF _LEDs+18, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 19;
    //    MOVF _LEDs+19, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 20;
    //    MOVF _LEDs+20, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 21;
    //    MOVF _LEDs+21, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 22;
    //    MOVF _LEDs+22, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 23;
    //    MOVF _LEDs+23, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 24;
    //    MOVF _LEDs+24, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 25;
    //    MOVF _LEDs+25, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに
    //
    ////    INCF _POS, F;
    //
    //    BANKSEL _LEDs + 26;
    //    MOVF _LEDs+26, W;
    //    MOVWF INDF0; //FSR0をWに
    //
    //    INCF FSR0L, F; //FSR0を次のアドレスに

    //    INCF _POS, F;


    //    DECF _loop, F;
    //
    //    BTFSC STATUS, 2; //1:??????0???????????
    //    GOTO _GET_DONE; //2:???????
    //
    //    GOTO _GET_DATA; //2:???????
    //_GET_DONE:

    //    BANKSEL _LEDs + 1;
    //    MOVF _LEDs + 1, W;
    //    MOVWF INDF0;
    //
    //    INCF FSR0L, F;
    //
    //    BANKSEL _LEDs + 2;
    //    MOVF _LEDs + 2, W;
    //    MOVWF INDF0;
    //
    //    INCF FSR0L, F;
    //
    //    BANKSEL _LEDs + 3;
    //    MOVF _LEDs + 3, W;
    //    MOVWF INDF0;
    //
    //    INCF FSR0L, F;
    //
    //    BANKSEL _LEDs + 4;
    //    MOVF _LEDs + 4, W;
    //    MOVWF INDF0;
    //
    //    INCF FSR0L, F;
    //
    //    BANKSEL _LEDs + 5;
    //    MOVF _LEDs + 5, W;
    //    MOVWF INDF0;
    //
    //    INCF FSR0L, F;

    //INCF FSR0L, F;

    //ここからWS2812と通信
    BANKSEL _loop;
    MOVLW 27;
    MOVWF _loop; //ループする回数

    MOVLW 0x20;
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
    NOP; //1:NOP;
    INCF FSR0L, F; //2:????????????????
    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 6; //5:?????6bit??0????????
    GOTO _SET_0_G_6; //6:
    BCF PORTA, 2; //7:
    GOTO _NEXT_0_G_6; //8:
_SET_0_G_6:
    NOP; //9:
    BCF PORTA, 2; //10:

_NEXT_0_G_6:
    // 5bit
    NOP; //1:NOP
    NOP; //2:NOP
    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 5; //5:?????5bit??0????????
    GOTO _SET_0_G_5; //6:
    BCF PORTA, 2; //7:Bit=0;
    GOTO _NEXT_0_G_5; //8:
_SET_0_G_5:
    NOP; //9:
    BCF PORTA, 2; //10:Bit=0;

_NEXT_0_G_5:
    // 4bit
    NOP; //1:NOP
    NOP; //2:NOP
    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 4; //5:?????4bit??0????????
    GOTO _SET_0_G_4; //6:
    BCF PORTA, 2; //7:Bit=0;
    GOTO _NEXT_0_G_4; //8:
_SET_0_G_4:
    NOP; //9:
    BCF PORTA, 2; //10:Bit=0;

_NEXT_0_G_4:
    // 3bit
    NOP; //1:NOP
    NOP; //2:NOP
    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 3; //5:?????3bit??0????????
    GOTO _SET_0_G_3; //6:
    BCF PORTA, 2; //7:Bit=0;
    GOTO _NEXT_0_G_3; //8:
_SET_0_G_3:
    NOP; //9:
    BCF PORTA, 2; //10:Bit=0;

_NEXT_0_G_3:
    // 2bit
    NOP; //1:
    NOP; //2:
    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 2; //5:?????2bit??0????????
    GOTO _SET_0_G_2; //6:
    BCF PORTA, 2; //7:Bit=0;
    GOTO _NEXT_0_G_2; //8:
_SET_0_G_2:
    NOP; //9:
    BCF PORTA, 2; //10:Bit=0;

_NEXT_0_G_2:
    // 1bit
    NOP; //1:
    DECF _loop, f; //2:????????????
    BANKSEL PORTA; //3:
    BSF PORTA, 2; //4:
    BTFSC WREG, 1; //5:?????1bit??0????????
    GOTO _SET_0_G_1; //6:
    BCF PORTA, 2; //7:
    GOTO _NEXT_0_G_1; //8:
_SET_0_G_1:
    NOP; //9:
    BCF PORTA, 2; //10:Bit=0;

_NEXT_0_G_1:
    // 0bit
    BTFSC STATUS, 2; //1:??????0???????????
    GOTO _LOOP_END; //2:???????
    BANKSEL PORTA; //3:Bit=1;
    BSF PORTA, 2; //4:
    BTFSC WREG, 0; //5:?????0bit??0????????
    GOTO _SET_7; //6:
    BCF PORTA, 2; //7:Bit=0;
    GOTO _NEXT_7; //8:

_LOOP_END:
    BANKSEL PORTA; //1:Bit=1;
    BSF PORTA, 2; //2:
    BTFSC WREG, 0; //3:?????0bit??0????????
    GOTO _SET; //4:
    BCF PORTA, 2; //5:Bit=0;
    GOTO _NEXT; //6:
_SET:
    NOP; //7:
    BCF PORTA, 2; //8:
_NEXT:
#endasm

    // reset period
    __delay_us(50);
}

#define GENTLY_INTERVAL 50  // ms
// 徐々にLEDの色を変化させる

void Gently_LEDs(void) {
    unsigned char r = 0x00;
    unsigned char g = 0x00;
    unsigned char b = 0xFF;
    char i;
    for (i = 0; i < 51; i++) {
        Set_Color(r, g, b, -1); // 色のセット
        Set_LEDs_16(); // 表示
        __delay_ms(GENTLY_INTERVAL);
        b -= 5;
        r += 5;
    }
    for (i = 0; i < 51; i++) {
        Set_Color(r, g, b, -1); // 色のセット
        Set_LEDs_16(); // 表示
        __delay_ms(GENTLY_INTERVAL);
        r -= 5;
        g += 5;
    }
    for (i = 0; i < 51; i++) {
        Set_Color(r, g, b, -1); // 色のセット
        Set_LEDs_16(); // 表示
        __delay_ms(GENTLY_INTERVAL);
        g -= 5;
        b += 5;
    }
}

void main(void) {

    unsigned char i;
    int j;

    ConfigureOscillator();
    __delay_ms(100);

    TRISAbits.TRISA2 = 0;
    LATAbits.LATA2 = 0;
    ANSELA = 0;

    while (1) {

        for (j = 0; j < 9; j++) {

            for (i = 0; i <= 254; i++) {
                Set_Color(i, 0, 0, j);
                Set_LEDs_16();
                __delay_ms(1);
            }
            for (i = 0; i <= 254; i++) {
                Set_Color((254 - i), 0, 0, j);
                Set_LEDs_16();
                __delay_ms(1);
            }

            for (i = 0; i <= 254; i++) {
                Set_Color(0, i, 0, j);
                Set_LEDs_16();
                __delay_ms(1);
            }
            for (i = 0; i <= 254; i++) {
                Set_Color(0, (254 - i), 0, j);
                Set_LEDs_16();
                __delay_ms(1);
            }

            for (i = 0; i <= 254; i++) {
                Set_Color(0, 0, i, j);
                Set_LEDs_16();
                __delay_ms(1);
            }
            for (i = 0; i <= 254; i++) {
                Set_Color(0, 0, (254 - i), j);
                Set_LEDs_16();
                __delay_ms(1);
            }
        }
        //        Gently_LEDs();
    }

}

void Set_Color(unsigned char R, unsigned char G, unsigned char B, char LED) {
    LEDs[LED * 3 + 0] = G;
    LEDs[LED * 3 + 1] = R;
    LEDs[LED * 3 + 2] = B;

    //
    //    switch (LED) {
    //        case 0:
    //            LEDs_0_r = R;
    //            LEDs_0_g = G;
    //            LEDs_0_b = B;
    //            break;
    //        case 1:
    //            LEDs_1_r = R;
    //            LEDs_1_g = G;
    //            LEDs_1_b = B;
    //            break;
    //        case 2:
    //            LEDs_2_r = R;
    //            LEDs_2_g = G;
    //            LEDs_2_b = B;
    //            break;
    //        case 3:
    //            LEDs_3_r = R;
    //            LEDs_3_g = G;
    //            LEDs_3_b = B;
    //            break;
    //        case 4:
    //            LEDs_4_r = R;
    //            LEDs_4_g = G;
    //            LEDs_4_b = B;
    //            break;
    //        case 5:
    //            LEDs_5_r = R;
    //            LEDs_5_g = G;
    //            LEDs_5_b = B;
    //            break;
    //        case 6:
    //            LEDs_6_r = R;
    //            LEDs_6_g = G;
    //            LEDs_6_b = B;
    //            break;
    //        case 7:
    //            LEDs_7_r = R;
    //            LEDs_7_g = G;
    //            LEDs_7_b = B;
    //            break;
    //        case 8:
    //            LEDs_8_r = R;
    //            LEDs_8_g = G;
    //            LEDs_8_b = B;
    //            break;
    //
    //        default:
    //            LEDs_0_r = R;
    //            LEDs_0_g = G;
    //            LEDs_0_b = B;
    //            LEDs_1_r = R;
    //            LEDs_1_g = G;
    //            LEDs_1_b = B;
    //            LEDs_2_r = R;
    //            LEDs_2_g = G;
    //            LEDs_2_b = B;
    //            LEDs_3_r = R;
    //            LEDs_3_g = G;
    //            LEDs_3_b = B;
    //            LEDs_4_r = R;
    //            LEDs_4_g = G;
    //            LEDs_4_b = B;
    //            LEDs_5_r = R;
    //            LEDs_5_g = G;
    //            LEDs_5_b = B;
    //            LEDs_6_r = R;
    //            LEDs_6_g = G;
    //            LEDs_6_b = B;
    //            LEDs_7_r = R;
    //            LEDs_7_g = G;
    //            LEDs_7_b = B;
    //            LEDs_8_r = R;
    //            LEDs_8_g = G;
    //            LEDs_8_b = B;
    //            break;
    //
    //
    //    }
}








