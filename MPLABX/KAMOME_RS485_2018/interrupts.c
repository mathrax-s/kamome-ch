///******************************************************************************/
///*Files to Include                                                            */
///******************************************************************************/
//
//#include <xc.h>         /* XC8 General Include File */
//
//#include <stdint.h>         /* For uint8_t definition */
//#include <stdbool.h>        /* For true/false definition */
//
//#include "user.h"
//int count;
//
//void interrupt isr(void) {
//    long tmp;
//    if (T0IF) {
//
//        if (strip == 1) {
//
//            for (int i = 0; i < 18; i++) {
//                tmp = color[0];
//
//                NeoBit(tmp & 1);
//                for (int j = 1; j < 24; j++) {
//                    NeoBit((tmp >>= 1) & 1);
//                }
//            }
//
//            for (int i = 0; i < 500; i++) {
//                NeoPin = 0;
//                NOP();
//            }
//
//        }
//
//        T0IF = 0;
//        //        T0IE = 0;
//    }
//
//
//}
//
//
