#ifndef __DS18B20_H
#define __DS18B20_H 
#include "../sys.h"

/*****************锟斤拷锟界单片锟斤拷锟斤拷锟�******************
											STM32
 * 锟侥硷拷			:	DS18B20锟斤拷锟斤拷锟铰度达拷锟斤拷锟斤拷h锟侥硷拷                   
 * 锟芥本			: V1.0
 * 锟斤拷锟斤拷			: 2024.8.13
 * MCU			:	STM32F103C8T6
 * 锟接匡拷			:	锟斤拷锟斤拷锟斤拷							
 * BILIBILI	:	锟斤拷锟界单片锟斤拷锟斤拷锟�
 * CSDN			:	锟斤拷锟界单片锟斤拷锟斤拷锟�
 * 锟斤拷锟斤拷			:	锟斤拷锟斤拷

**********************BEGIN***********************/

/***************锟斤拷锟斤拷锟皆硷拷锟斤拷锟斤拷锟斤拷锟�****************/
//DS18B20锟斤拷锟脚宏定锟斤拷						

#define DS18B20_GPIO_PORT		GPIOB
#define DS18B20_GPIO_PIN		GPIO_Pin_1
#define DS18B20_GPIO_CLK   	RCC_APB2Periph_GPIOB

/*********************END**********************/
//锟斤拷锟阶刺�锟斤拷锟斤拷
#define OUT 1
#define IN  0

//锟斤拷锟斤拷DS18B20锟斤拷锟斤拷锟斤拷锟斤拷叩偷锟狡�
#define DS18B20_Low  GPIO_ResetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)
#define DS18B20_High GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)		
		
u8 DS18B20_Init(void);//锟斤拷始锟斤拷DS18B20
short DS18B20_Get_Temp(void);//锟斤拷取锟铰讹拷
void DS18B20_Start(void);//锟斤拷始锟铰讹拷转锟斤拷
void DS18B20_Write_Byte(u8 dat);//写锟斤拷一锟斤拷锟街斤拷
u8 DS18B20_Read_Byte(void);//锟斤拷锟斤拷一锟斤拷锟街斤拷
u8 DS18B20_Read_Bit(void);//锟斤拷锟斤拷一锟斤拷位
void DS18B20_Mode(u8 mode);//DS18B20锟斤拷锟斤拷锟斤拷锟侥Ｊ斤拷锟斤拷锟�
u8 DS18B20_Check(void);//锟斤拷锟斤拷欠锟斤拷锟斤拷DS18B20
void DS18B20_Rst(void);//锟斤拷位DS18B20   

#endif














