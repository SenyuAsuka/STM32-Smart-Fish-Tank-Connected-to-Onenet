
//单片机头文件
#include "stm32f10x.h"

//硬件驱动
#include "key.h"
#include "delay.h"
#include "led.h"
#include "relay1.h"
#include "Servo.h"
uint8_t Angle;

/*
************************************************************
*	函数名称：	Led_Init
*
*	函数功能：	按键初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void KEY_EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    // 开启GPIOB和AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
    
    // 配置PB12、13、14、15为上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 将PB12连接到EXTI12
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    // 将PB13连接到EXTI13
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_Init(&EXTI_InitStructure);
    
    // 将PB14连接到EXTI14
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_Init(&EXTI_InitStructure);
    
    // 将PB15连接到EXTI15
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource15);
    EXTI_InitStructure.EXTI_Line = EXTI_Line15;
    EXTI_Init(&EXTI_InitStructure);
    
    // 配置NVIC
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//void EXTI15_10_IRQHandler(void)
//{

//	DelayXms(10);
//	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) ==0)
//	{
//		if(led_info.Led_Status == LED_ON)
//			{
//				Led_Set(LED_OFF);
//			}
//		else	Led_Set(LED_ON);
//	}
//	EXTI_ClearITPendingBit(EXTI_Line12);
//	
//	
//}

void EXTI15_10_IRQHandler(void)
{

	DelayXms(10);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) ==0)
	{
		if(relay3_info.Relay3_Status == RELAY3_ON)
			{
				Relay3_Set(RELAY3_OFF);
			}
		else	Relay3_Set(RELAY3_ON);
	}
	EXTI_ClearITPendingBit(EXTI_Line12);
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) ==0)
	{
		if(relay2_info.Relay2_Status == RELAY2_ON)
			{
				Relay2_Set(RELAY2_OFF);
			}
		else	Relay2_Set(RELAY2_ON);
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
	
	//
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) ==0)
	{
		if(relay1_info.Relay1_Status == RELAY1_ON)
			{
				Relay1_Set(RELAY1_OFF);
			}
		else	Relay1_Set(RELAY1_ON);
	}
	EXTI_ClearITPendingBit(EXTI_Line14);
	
	
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) ==0)
	{
		Angle += 90;				//角度变量自增30
			if (Angle > 90)			//角度变量超过180后
			{
				Angle = 0;				//角度变量归零
			}
			Servo_SetAngle(Angle);
		}
					//设置舵机的角度为角度变量
	
	EXTI_ClearITPendingBit(EXTI_Line15);
	
}



