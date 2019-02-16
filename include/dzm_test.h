
#ifndef _DZM_TEST_H_ 
#define _DZM_TEST_H_

#define GPK1_1_CON	    (*(volatile u32 *)0x11000060)
#define GPK1_1_DAT	    (*(volatile u32 *)0x11000064)
#define GPL2_0_CON      (*(volatile u32 *)0x11000100)
#define GPL2_0_DAT      (*(volatile u32 *)0x11000104)
#define GPA1_CON		(*(volatile u32 *)0x11400020)
#define GPA1_PUD        (*(volatile u32 *)0x11400028)

#define LED3_ON		\
				do{\
					GPK1_1_CON &= ~0xf0;\
					GPK1_1_CON |= 0x10;\
					GPK1_1_DAT |= 0x02;\
				  }while(0)

#define LED3_OFF	GPK1_1_DAT &= ~0x02

#define LED2_ON		\
				do{\
					GPL2_0_CON &= ~0x0f;\
					GPL2_0_CON |= 0x01;\
					GPL2_0_DAT |= 0x01;\
				}while(0)

#define LED2_OFF	GPL2_0_DAT &= ~0x01

#define UART2_PIN_INIT	   \
						do{\
							GPA1_PUD &= ~0x0f;\
							GPA1_CON &= ~0xff;\
							GPA1_CON |= 0x22;\
						}while(0)
#endif
