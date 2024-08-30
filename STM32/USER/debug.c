#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "string.h"
#include "stdio.h"
#include "debug.h"


struct __FILE {
    int dummy;
};
 
/* You need this if you want use printf */
/* Struct FILE is implemented in stdio.h */
FILE __stdout;
 
int fputc(int ch, FILE *f) {
    /* Do your stuff here */
    /* Send your custom byte */
    /* Send byte to USART */
    db_DEBUG_SendChar(ch);
    
    /* If everything is OK, you have to return character written */
    return ch;
    /* If character is not correct, you can return EOF (-1) to stop writing */
    //return -1;
}

//==============================Khai bao TX, RX===============================
#define TX GPIO_Pin_9
#define RX GPIO_Pin_10
//==============================kich thuc mang===============================
#define string_size 80
//==============================khai bao mang==============================
volatile char RX_FLAG_END_LINE = 0;
char RRX[string_size];
volatile unsigned int RXI = 0;
volatile char temp_char;
char Number[50];
//==============================Khoi tao GPIO va USART==============================
GPIO_InitTypeDef GPIO_init1;
USART_InitTypeDef USART_init1;
//==============================Cau hinh can TX, RX cau hinh USART==============================
	void db_DEBUG_Init(unsigned int BaudRates)
	{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_init1.GPIO_Pin = TX;
	GPIO_init1.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_init1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_init1);
	
	GPIO_init1.GPIO_Pin = RX;
	GPIO_init1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_init1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_init1);
	
	USART_Cmd(USART1, ENABLE);
	USART_init1.USART_BaudRate = BaudRates;
	USART_init1.USART_WordLength =USART_WordLength_8b;
	USART_init1.USART_StopBits = USART_StopBits_1;
	USART_init1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_init1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_init1.USART_Parity = USART_Parity_No;
	USART_Init(USART1, &USART_init1);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
	}
//==============================Ham in mang ky tu==============================
	void db_DEBUG_Putchar_RRX(void)
	{
		db_DEBUG_Putchar(RRX);
	}
//==============================Co bao co ky tu \n==============================
	int db_DEBUG_flag(void)
	{
		if(RX_FLAG_END_LINE == 1)
			{	
				RX_FLAG_END_LINE = 0;
				return 1;
			}
			return 0;
	}
//==============================So sanh chuoi chuyen xuong voi chuoi cai dat ==============================

	int db_DEBUG_compare(char *string)
	{
			
				if(strstr(RRX,string)!=NULL)
					{
						return 1;
					}
					return 0;
	}
	
//==============================Gui tung ky tu==============================
	void db_DEBUG_SendChar(char _varChar)
	{
		USART_SendData(USART1,_varChar);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	}
	
//==============================Gui moi chuoi ky tu==============================
	void db_DEBUG_Putchar(char *_varString)
	{
		while(*_varString)
		{
			db_DEBUG_SendChar(*_varString);
			_varString++;
			}
	}

//==============================Gui kieu ky tu so kieu INT============================== 
	void db_DEBUG_Number(int _varNumber)
	{
			sprintf(Number,"%d.",_varNumber);
			db_DEBUG_Putchar(Number);
	}
	
//==============================Ham ngat UART==============================
	void USART1_IRQHandler()
	{
		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
		{
			temp_char = USART_ReceiveData(USART1);
		
			if(temp_char != '\n')
			{	
				RRX[RXI] = temp_char;
				RXI++;
			}
			else
			{
				RRX[RXI] = 0x00;
				RX_FLAG_END_LINE=1;
				RXI = 0;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}

