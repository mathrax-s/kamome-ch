///******************************************************************************/
///* Files to Include                                                           */
///******************************************************************************/
//
//#include <xc.h>         /* XC8 General Include File */
//
//#include <stdint.h>         /* For uint8_t definition */
//#include <stdbool.h>        /* For true/false definition */
//
//#include "user.h"
//
///******************************************************************************/
///* User Functions                                                             */
///******************************************************************************/
//
////uint8_t NeoGreen [NeoNum];
////uint8_t NeoBlue [NeoNum];
////uint8_t NeoRed [NeoNum];
//
////uint16_t color[18];
//
//void InitApp(void) {
//
//
//}
//
//void NeoBit(bool Bit) {
//    if (Bit) {
//        NeoPin = 1;
//        NOP();
//        NOP();
//        NOP();
//        NOP();
//
//        NeoPin = 0;
//        NOP();
//
//    } else {
//        NeoPin = 1;
//        NOP();
//
//        NeoPin = 0;
//
//        NOP();
//        NOP();
//        NOP();
//        NOP();
//    }
//
//
//}
//
//void NeoInit(void) {
//    uint8_t NeoPixel;
//
////    for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++) {
////
////        NeoGreen[NeoPixel] = 20;
////        NeoBlue[NeoPixel] = 20;
////        NeoRed[NeoPixel] = 64;
////
////    }
//}
//
//void NeoDraw(void) {
//
////    color[0] = 0b111100001111000011110000;
////    color[0] = 0b111100001111111111111111;
//
////    uint8_t NeoPixel;
////    int8_t BitCount;
////
////    for (NeoPixel = 0; NeoPixel < NeoNum; NeoPixel++) {
//////        for (BitCount = 7; BitCount >= 0; BitCount--) {
//////            NeoBit(bittest(NeoGreen[NeoPixel], BitCount));
//////        }
//////
//////        for (BitCount = 7; BitCount >= 0; BitCount--)
//////            NeoBit(bittest(NeoRed[NeoPixel], BitCount));
//////
//////        for (BitCount = 7; BitCount >= 0; BitCount--)
//////            NeoBit(bittest(NeoBlue[NeoPixel], BitCount));
////
//////        color[NeoPixel] = NeoGreen[NeoPixel] << 16 | NeoRed[NeoPixel] << 8 | NeoBlue[NeoPixel];
////    }
//
//}
//
//void NeoRotate(void) {
////    uint8_t NeoPixel;
////    for (NeoPixel = 0; NeoPixel < NeoNum - 1; NeoPixel++) {
////        NeoGreen[NeoPixel] = NeoGreen[NeoPixel + 1];
////        NeoBlue[NeoPixel] = NeoBlue[NeoPixel + 1];
////        NeoRed[NeoPixel] = NeoRed[NeoPixel + 1];
////    }
////    NeoGreen[NeoNum - 1] = NeoGreen[0];
////    NeoBlue[NeoNum - 1] = NeoBlue[0];
////    NeoRed[NeoNum - 1] = NeoRed[0];
//}
//
