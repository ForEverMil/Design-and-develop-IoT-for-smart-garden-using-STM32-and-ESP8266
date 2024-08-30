#ifndef __DHT11_H  
#define __DHT11_H 
  
#include "stm32f10x.h" 
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stdio.h"
#include "delay.h"
  
#define DHT11_GPIO        GPIOA
#define DHT11_PIN         GPIO_Pin_6
#define DHT11_RCC         RCC_APB2Periph_GPIOA
#define DHT11_SetBit()    GPIO_SetBits(DHT11_GPIO,DHT11_PIN) 
#define DHT11_ResetBit()  GPIO_ResetBits(DHT11_GPIO,DHT11_PIN)
#define DHT11_ReadBit()   GPIO_ReadInputDataBit(DHT11_GPIO,DHT11_PIN)

static void DHT11_Input(void); 
static void DHT11_Output(void);

void DHT11_Start(void); 
u16 DHT11_ReadByte(void); 
u16 DHT11_ReadData(void);
u16 DHT11_GetTemp(void);
u16 DHT11_GetHem(void); 

#endif 