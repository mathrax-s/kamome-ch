/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */
//#define NeoPin LATAbits.LATA2
//#define NeoNum 9//18
////#define RAND_MAX 64
////#define ALL_OUT 0x00
////#define ALL_IN  0xFF

#define _XTAL_FREQ      32000000L
#define SYS_FREQ        32000000L
#define FCY             SYS_FREQ/4

//#define __delay(x) _delay((unsigned long)((x)))
//#define __delay_us(x) _delay((unsigned long)((x)*(SYS_FREQ/4000000UL)))
//#define __delay_ms(x) _delay((unsigned long)((x)*(SYS_FREQ/4000UL)))

//#define bittest(D,i) ((D & (0x01 << i))>>i)
//#define bittest(D,i) ((D >> i ) & 0x01)
//extern uint8_t NeoGreen [NeoNum];
//extern uint8_t NeoBlue [NeoNum];
//extern uint8_t NeoRed [NeoNum];
//extern uint8_t
/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
//
//void NeoBit(uint8_t Bit);
//void NeoInit(void);
//void NeoDraw(void);
//void NeoRotate(void);
