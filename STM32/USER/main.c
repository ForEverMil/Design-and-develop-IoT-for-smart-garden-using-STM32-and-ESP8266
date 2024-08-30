#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "queue.h"                      // ARM.FreeRTOS::RTOS:Core
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "dht11.h"
#include "uart.h" 
#include "stdio.h"
#include "Delay.h"

__IO uint32_t ADC_ARRAY[2];
long map(long x, long in_min, long in_max, long out_min, long out_max);

typedef struct
{
	uint8_t Sensor_Temperature;
	uint8_t Sensor_Humidity;
	uint8_t Sensor_SoilMoisture;
}sensor_DataStruct_t;

xQueueHandle xQueue;

void SYS_Init(void);
void ADC_Inits(void);
void Relay_Inits(void);

void TaskReadSensor(void *p); 
void TaskSendSensor(void *p); 
void TaskGetControl(void *p);
void TaskProcess(void *p);
int main (void){
	xQueue = xQueueCreate(10, sizeof(sensor_DataStruct_t));
	SYS_Init();
	xTaskCreate(TaskReadSensor, (const char*) "Read", 512, NULL, 1, NULL);
	xTaskCreate(TaskSendSensor, (const char*) "Send", 512, NULL, 1, NULL);
	xTaskCreate(TaskGetControl, (const char*) "Send", 512, NULL, 1, NULL);
	vTaskStartScheduler();
}

void TaskReadSensor(void *p)
{
	sensor_DataStruct_t sendDataSensor = {0,0,0};

	while(1)
	{
		unsigned char i = 0;
		unsigned int SumSoilMoisture  = 0;
		DHT11_ReadData();
		sendDataSensor.Sensor_Temperature 	= DHT11_GetTemp()/256;
		sendDataSensor.Sensor_Humidity			= DHT11_GetHem()/256;
		for(i=0; i<50; i++)
		{
			SumSoilMoisture += ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1)/10;
		}
		SumSoilMoisture /= 50;
		if(SumSoilMoisture < 290)
		{
			SumSoilMoisture = 290;
		}
		else if(SumSoilMoisture > 390)
		{
			SumSoilMoisture = 390;
		}
		
		sendDataSensor.Sensor_SoilMoisture 	= (uint8_t)map(SumSoilMoisture,290,390,100, 0);
		
		if(xQueue != 0)
		{
			xQueueSend(xQueue, (void*)&sendDataSensor, (portTickType)0);
		}
		vTaskDelay(2000/portTICK_PERIOD_MS);   
	}
}

void TaskSendSensor(void *p)
{
	char ARR_Number[50];
	
	while(1)
	{
		sensor_DataStruct_t getDataSensor;
		if(xQueueReceive(xQueue, (void*)&getDataSensor, (portTickType)0))
		{
			//UART2_SendByte((uint8_t*)(&getDataSensor), sizeof(getDataSensor));
			
			sprintf(ARR_Number,"%d %d %d !",getDataSensor.Sensor_Temperature, getDataSensor.Sensor_Humidity, getDataSensor.Sensor_SoilMoisture);
			UART2_SendString(ARR_Number);
		}
		vTaskDelay(10/portTICK_PERIOD_MS);   
	}
}

void TaskGetControl(void *p)
{
	while(1)
	{
		if(Flag2_Receive == 1)
		{
			Flag2_Receive = 0;
			/*
			UART1_SendChar(Array2_Receive[0]);
			UART1_SendString(" ");
			UART1_SendChar(Array2_Receive[2]);
			UART1_SendString("\n");
			*/
			if(Array2_Receive[0] == '0')
			{
				UART1_SendString("Relay1: OFF ");
				GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
			}
			else if(Array2_Receive[0] == '1')
			{
				UART1_SendString("Relay1: ON ");
				GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
			}
	
		}
		vTaskDelay(100/portTICK_PERIOD_MS);
	}

}

void TaskProcess(void *p)
{
	
}

void SYS_Init(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	_init_TIM3();
	INIT_UART_1(9600);
	INIT_UART_2(9600);
	DHT11_Start();
	ADC_Inits();
	Relay_Inits();
}

void ADC_Inits(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_ADCCLKConfig (RCC_PCLK2_Div6);

	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO |RCC_APB2Periph_ADC1 ,	ENABLE ) ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_InjectedSequencerLengthConfig(ADC1, 2);
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_7Cycles5);
	ADC_InjectedChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_7Cycles5);

	ADC_ExternalTrigInjectedConvConfig( ADC1, ADC_ExternalTrigInjecConv_None );

	ADC_Cmd ( ADC1 , ENABLE ) ;

	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	ADC_AutoInjectedConvCmd( ADC1, ENABLE );
	ADC_SoftwareStartInjectedConvCmd ( ADC1 , ENABLE ) ;
}

void Relay_Inits(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB,	ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
