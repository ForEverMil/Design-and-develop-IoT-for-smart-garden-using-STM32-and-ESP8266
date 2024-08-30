#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stdint.h>
#include <Delay.h>


// Init timer for Microseconds delays
void _init_TIM3() {
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	// Time base configuration
	TIM_TimeBaseInitTypeDef TIM;
	
	TIM.TIM_Prescaler = 60-1;
	TIM.TIM_Period = 50000-1;
	TIM.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM);

	// Enable counter for TIM2
}



// Do delay for nTime milliseconds
void delay_us(uint32_t uSecs) {
	TIM_Cmd(TIM3,ENABLE);

	while(TIM3->CNT <uSecs);
	TIM3->CNT =0;
	TIM_Cmd(TIM3,DISABLE);
}

// Do delay for nTime microseconds
void delay_ms(uint32_t mSecs) {
	// Init and start timer
	int i = 0;
	for(i=0;i< mSecs; i++){
		delay_us(1000);
	}
}