#include "dht11.h" 
static void DHT11_Input(void);  
static void DHT11_Output(void); 

u8 DHT11_hem_high,DHT11_hem_low,DHT11_temp_high,DHT11_temp_low;   
  
static void DHT11_Input(void) 
{  
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(DHT11_RCC,ENABLE);  
   
  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
   
  GPIO_Init(DHT11_GPIO, &GPIO_InitStructure);
} 
static void DHT11_Output(void)
{  
  GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_APB2PeriphClockCmd(DHT11_RCC,ENABLE);
  GPIO_InitStructure.GPIO_Pin = DHT11_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   
  GPIO_Init(DHT11_GPIO, &GPIO_InitStructure);
}  
  

void DHT11_Start(void)
{  
//  delay_init();
  DHT11_Output();
  DHT11_hem_high   = 0;
  DHT11_hem_low    = 0; 
  DHT11_temp_high  = 0;  
  DHT11_temp_low   = 0;  
}  
u16 DHT11_ReadByte(void)
{ 
  u8 temp=0,i,cout;
  DHT11_Input();  
  for(i=0;i<8;i++) 
  {
    cout=1;
    while(!DHT11_ReadBit() && cout++);
    delay_us(30);
    temp = temp << 1;
    if(DHT11_ReadBit() == Bit_SET)
    {  
      temp |=1; 
    }  
    cout=1;  
    while(DHT11_ReadBit() && cout++);  
  }  
  return temp;//??????temp  
}  
u16 DHT11_ReadData(void)
{ 
  u16 cout = 1;
  u16 temp_high,temp_low,hem_high,hem_low,Check;
  DHT11_Output();
   
  DHT11_ResetBit();
  delay_ms(20);
  DHT11_SetBit();
  delay_us(30);

  DHT11_Input();
  if(DHT11_ReadBit() == Bit_RESET)  
  {  
    cout = 1;
    while(!DHT11_ReadBit() && cout++); 
      
    cout = 1;
    while(DHT11_ReadBit() && cout++);  
      
    hem_high = DHT11_ReadByte();
    hem_low  = DHT11_ReadByte();
    temp_high  = DHT11_ReadByte();
    temp_low   = DHT11_ReadByte();
    Check = DHT11_ReadByte();

    if(Check == ( temp_high + temp_low + hem_high + hem_low ))
    {  
      DHT11_hem_high = hem_high;//????????  
      DHT11_hem_low = hem_low;//????????  
      DHT11_temp_high = temp_high;//????????  
      DHT11_temp_low  = temp_low;//????????  
        
      return 1;
    }
    else  
    {  
      return 0;
    }  
  } 
  return 0;  
}  
  
u16 DHT11_GetTemp(void) 
{  
  return(DHT11_temp_high <<8 | DHT11_temp_low);  
}  
u16 DHT11_GetHem(void)//?????  
{ 
  return(DHT11_hem_high <<8 | DHT11_hem_low);
}  