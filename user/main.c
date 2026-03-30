#include "stm32f10x.h"
#include "onenet.h"
#include "esp8266.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"
#include "key.h"
#include "beep.h"
#include "ds18b20.h"
#include "relay1.h"
#include "Servo.h"
#include "AD.h"
#include "TDS.h"
#include "TS.h"
#include "PH.h"
#include "dht11.h"
#include <string.h>

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"mqtts.heclouds.com\",1883\r\n"

// ================= 全局变量定义 =================
float water_temp = 0.0f;    // 水温
float TDS_Data = 0.0f;      // 水质 TDS
float PH_Data = 0.0f;       // 水质 PH
u8 environment_humi = 0;    // 环境湿度 (DHT11)

void Display_Init(void);
void Refresh_Data(void);

/*
************************************************************
*	函数名称：	Hardware_Init
*	函数功能：	硬件初始化
************************************************************
*/
void Hardware_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置
	
	Delay_Init();									//systick初始化
	
	Usart1_Init(115200);							//串口1，打印信息用
	Usart2_Init(115200);							//串口2，驱动ESP8266用
	
	Relay_Init();
	Servo_Init();
	KEY_EXTI_Init();								//按键初始化
	OLED_Init();									//OLED屏幕初始化
	
    // --- DS18B20 初始化 ---
    if(DS18B20_Init())
    {
        UsartPrintf(USART_DEBUG, "DS18B20 Init Failed!\r\n");
        OLED_ShowString(0,0,"DS18B20 Error",OLED_8X16);
    }
    else
    {
        UsartPrintf(USART_DEBUG, "DS18B20 Init OK!\r\n");
    }

    // --- DHT11 初始化 (新增) ---
    // 检测DHT11是否存在
    if(DHT11_Init()) 
    {
        UsartPrintf(USART_DEBUG, "DHT11 Init Failed!\r\n");
        OLED_ShowString(0,16,"DHT11 Error",OLED_8X16);
        DelayMs(1000); // 报错停留一下
    }
    else
    {
         UsartPrintf(USART_DEBUG, "DHT11 Init OK!\r\n");
    }

	AD_Init();								//AD初始化
	Beep_Init();							//蜂鸣器初始化

	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
	OLED_Clear();
	OLED_ShowString(0,0,"Hardware init OK",OLED_8X16);
	OLED_Update();
	DelayMs(1000);
	Display_Init(); //OLED界面初始化
}

/*
************************************************************
*	函数名称：	main
*	函数功能：	主函数
************************************************************
*/
int main(void)
{
	unsigned short timeCount = 0;	//发送间隔变量
	unsigned char *dataPtr = NULL;
	
	Hardware_Init();				//初始化外围硬件
	ESP8266_Init();					//初始化ESP8266
	
	UsartPrintf(USART_DEBUG, "Connect MQTTs Server...\r\n");
	OLED_ShowString(0,0,"Connect MQTTs Server...",OLED_6X8);
	OLED_Update();
    
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
	    DelayXms(500);
	
	UsartPrintf(USART_DEBUG, "Connect MQTT Server Success\r\n");
	OLED_ShowString(0,22,"Connect MQTT Server Success...",OLED_6X8);
	OLED_Update();
    
	while(OneNet_DevLink())			//接入OneNET
	    DelayXms(500);
    
	OLED_Clear();
	OneNET_Subscribe(); // 订阅Topic，接收云端命令
	
	while(1)
	{
		if(++timeCount >= 200) //发送间隔约 2s (10ms * 200)
		{
			// 1. 获取水温 (DS18B20)
            // 注意：你的DS18B20驱动内部乘以了0.625(放大了10倍)，所以这里必须除以10
			water_temp = (float)DS18B20_Get_Temp() / 10.0f; 
            
            // 2. 获取环境温湿度 (DHT11) - 新增
            // 传入变量地址，函数执行后会更新 environment_temp 和 environment_humi 的值
            DHT11_Read_Data(&environment_temp, &environment_humi);

            // 3. 获取其他传感器数据 (ADC)
			TDS_Data = GateTDS_GetData_PPM();
			PH_Data = GatePH_GetData();
            
            // 4. 报警与显示
			Beep_Alarm();
			Refresh_Data(); // 刷新屏幕显示
            
            // 5. 上报云端
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");
			OneNet_SendData();
			
			timeCount = 0;
			ESP8266_Clear();
		}
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);
        
		DelayXms(10);
	}
}

void Display_Init(void)
{
	OLED_Clear();
	OLED_Printf(0, 0, OLED_8X16,"PH：", 10);
	OLED_Printf(0, 16, OLED_8X16,"TDS：", 10);
	OLED_Printf(0, 32, OLED_8X16,"水温： ", 10);
	OLED_Printf(0, 48, OLED_8X16,"湿度： ", 10);
	OLED_Update();
}

void Refresh_Data(void)
{
	// 只局部刷新数据区域，避免屏幕闪烁
    OLED_Clear(); 
    
	OLED_ShowImage(112, 0, 16, 16, WIFI);
	
    // PH值
    OLED_Printf(0, 0, OLED_8X16,"PH:%4.2f ", PH_Data);
	
    // TDS值
    OLED_Printf(0, 16, OLED_8X16,"水质:%.0f PPM", TDS_Data);
	
    // 水温值
    OLED_Printf(0, 32, OLED_8X16,"水温:%3.1f C  ", water_temp); 
    
    // 湿度值 (使用全局变量 environment_humi)
    OLED_Printf(0, 48, OLED_8X16, "湿度:%d%%", (int)environment_humi);
    
    // 如果需要显示继电器状态，可在此处添加
    // if(relay2_info.Relay2_Status) ... 
    
	OLED_Update();
}
