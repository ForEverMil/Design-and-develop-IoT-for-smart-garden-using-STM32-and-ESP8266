

#ifndef _CONFIG_STM32F10x_
#define _CONFIG_STM32F10x_
#include "stm32f10x.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>





#define GPIO_REGISTER_CRL	0x00
#define GPIO_REGISTER_CRH	0x04
#define GPIO_REGISTER_IDR	0x08
#define GPIO_REGISTER_ODR	0x0C
#define GPIO_REGISTER_BSRR	0x10
#define GPIO_REGISTER_BRR	0x14

#define GPIO_BASE_PORT_A	0x40010800
#define GPIO_BASE_PORT_B	0x40010C00
#define GPIO_BASE_PORT_C	0x40011000
#define GPIO_BASE_PORT_D	0x40011400
#define GPIO_BASE_PORT_E	0x40011800
#define GPIO_BASE_PORT_F	0x40011C00 
#define GPIO_BASE_PORT_G	0x40012000


#define MODE_IN_A			0
#define MODE_IN_FLOAT	1
#define MODE_IN_PULL	2
#define MODE_IN_RESE	3

#define MODE_GOUT_PUSHPULL	0
#define MODE_GOUT_OPENDRAIN	1
#define MODE_FOUT_PUSHPULL	2
#define MODE_FOUT_OPENDRAIN	3

#define MODE_IN					0
#define MODE_OUT_10MHZ	1
#define MODE_OUT_2MHZ		2
#define MODE_OUT_50MHZ	3





struct STM_MODE_LOW
{
	unsigned long MODE0 : 2;
	unsigned long CNF0	: 2;
	unsigned long MODE1 : 2;
	unsigned long CNF1	: 2;
	unsigned long MODE2 : 2;
	unsigned long CNF2	: 2;
	unsigned long MODE3 : 2;
	unsigned long CNF3	: 2;
	unsigned long MODE4 : 2;
	unsigned long CNF4	: 2;
	unsigned long MODE5 : 2;
	unsigned long CNF5	: 2;
	unsigned long MODE6 : 2;
	unsigned long CNF6	: 2;
	unsigned long MODE7 : 2;
	unsigned long CNF7	: 2;
};

struct STM_MODE_HIGH
{
	unsigned long MODE8 : 2;
	unsigned long CNF8	: 2;
	unsigned long MODE9 : 2;
	unsigned long CNF9	: 2;
	unsigned long MODE10: 2;
	unsigned long CNF10	: 2;
	unsigned long MODE11: 2;
	unsigned long CNF11	: 2;
	unsigned long MODE12: 2;
	unsigned long CNF12	: 2;
	unsigned long MODE13: 2;
	unsigned long CNF13	: 2;
	unsigned long MODE14: 2;
	unsigned long CNF14	: 2;
	unsigned long MODE15: 2;
	unsigned long CNF15	: 2;
};

struct STM_PORT
{
	unsigned long PIN0 :1;
	unsigned long PIN1 :1;
	unsigned long PIN2 :1;
	unsigned long PIN3 :1;
	unsigned long PIN4 :1;
	unsigned long PIN5 :1;
	unsigned long PIN6 :1;
	unsigned long PIN7 :1;
	unsigned long PIN8 :1;
	unsigned long PIN9 :1;
	unsigned long PIN10:1;
	unsigned long PIN11:1;
	unsigned long PIN12:1;
	unsigned long PIN13:1;
	unsigned long PIN14:1;
	unsigned long PIN15:1;
};

#define PORTA_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_A + GPIO_REGISTER_IDR))
#define PORTA_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_A + GPIO_REGISTER_ODR))
#define PORTA_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_A + GPIO_REGISTER_CRH))
#define PORTA_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_A + GPIO_REGISTER_CRL))	


#define PORTB_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_B + GPIO_REGISTER_IDR))
#define PORTB_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_B + GPIO_REGISTER_ODR))
#define PORTB_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_B + GPIO_REGISTER_CRH))
#define PORTB_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_B + GPIO_REGISTER_CRL))
#define	PORTB_OUT_PORT	(*(volatile unsigned long*)(GPIO_BASE_PORT_B	+ GPIO_REGISTER_ODR))
	

#define PORTC_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_C + GPIO_REGISTER_IDR))
#define PORTC_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_C + GPIO_REGISTER_ODR))
#define PORTC_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_C + GPIO_REGISTER_CRH))
#define PORTC_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_C + GPIO_REGISTER_CRL))
	

#define PORTD_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_D + GPIO_REGISTER_IDR))
#define PORTD_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_D + GPIO_REGISTER_ODR))
#define PORTD_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_D + GPIO_REGISTER_CRH))
#define PORTD_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_D + GPIO_REGISTER_CRL))
	

#define PORTE_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_E + GPIO_REGISTER_IDR))
#define PORTE_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_E + GPIO_REGISTER_ODR))
#define PORTE_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_E + GPIO_REGISTER_CRH))
#define PORTE_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_E + GPIO_REGISTER_CRL))
	

#define PORTF_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_F + GPIO_REGISTER_IDR))
#define PORTF_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_F + GPIO_REGISTER_ODR))
#define PORTF_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_F + GPIO_REGISTER_CRH))
#define PORTF_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_F + GPIO_REGISTER_CRL))


#define PORTG_IN  (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_G + GPIO_REGISTER_IDR))
#define PORTG_OUT (*(volatile struct STM_PORT *) (GPIO_BASE_PORT_G + GPIO_REGISTER_ODR))
#define PORTG_CRH (*(volatile struct STM_MODE_HIGH *) (GPIO_BASE_PORT_G + GPIO_REGISTER_CRH))
#define PORTG_CRL (*(volatile struct STM_MODE_LOW  *) (GPIO_BASE_PORT_G + GPIO_REGISTER_CRL))
#endif

