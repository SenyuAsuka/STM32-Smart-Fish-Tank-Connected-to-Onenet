

//单片机头文件
#include "stm32f10x.h"

//硬件驱动
#include "beep.h"

extern float water_temp;


/*
************************************************************
*	函数名称：	Beep_Init
*
*	函数功能：	蜂鸣器初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Beep_Init(void)
{

	GPIO_InitTypeDef gpio_initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//打开GPIOB的时钟
	gpio_initstruct.GPIO_Mode = GPIO_Mode_Out_PP;				//设置为输出
	gpio_initstruct.GPIO_Pin = GPIO_Pin_4;						//将初始化的Pin脚
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;				//可承载的最大频率
	GPIO_Init(GPIOA, &gpio_initstruct);							//初始化GPIO
	
}
void Beep_Start(void)
{
GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

void Beep_Stop(void)
{
GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void Beep_Alarm(void)
{
	if(water_temp<=10.0||water_temp>=30.0)
	{
		Beep_Start();
	}
	else  Beep_Stop();
		
}

