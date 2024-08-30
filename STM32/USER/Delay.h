#include "stm32f10x.h" // Device header
#define DELAY_TIM_FREQUENCY_US 1000000		/* = 1MHZ -> timer runs in microseconds */
#define DELAY_TIM_FREQUENCY_MS 1000			/* = 1kHZ -> timer runs in milliseconds */


/*
 *   Declare Functions
 */
extern void delay_ms(uint32_t nTime);
extern void delay_us(uint32_t nTime);
void _init_TIM3();