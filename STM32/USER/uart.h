 
/*
  ******************************************************************************
  * @file		Uart.h                                                              *
  * @author	Nguyen Quang Bien                                                  *
  * @date		00/00/0000                                                         *
  ******************************************************************************
*/
	
#ifndef __UART__
#define __UART__
#include "stm32f10x.h"
#ifdef __cplusplus
 extern "C" {
#endif
	 
#define  UART1_BAUDRATE (115200)
#define  UART2_BAUDRATE (115200)
#define  UART3_BAUDRATE (19200)
	 
#define string_size 20
	 
extern char Flag1_Receive;
extern char Array1_Receive[];
extern char Count1_Data;
	 
extern char Flag2_Receive;
extern char Array2_Receive[];
extern char Count2_Data;

extern char Flag3_Receive;
extern char Array3_Receive[];
extern char Count3_Data;	 
	 
void INIT_UART(void);
	 
void INIT_UART_1(unsigned int BaudRates);
void UART1_SendChar(char data);
void UART1_SendString(char *data);
void UART1_SendByte(uint8_t *data, uint8_t sizes); 

void INIT_UART_2(unsigned int BaudRates);
void UART2_SendChar(char data);
void UART2_SendString(char *data);
void UART2_SendByte(uint8_t *data, uint8_t sizes); 

void INIT_UART_3(unsigned int BaudRates);
void UART3_SendChar(char data);		 
void UART3_SendString(char *data);
char* RETURN_HI100(void);

#ifdef __cplusplus
}
#endif

#endif

