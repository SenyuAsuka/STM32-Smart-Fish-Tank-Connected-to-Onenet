#include "stm32f10x.h"
#include "PH.h"
#include "AD.h"
#include "delay.h"

/**
  * 函数功能：获取pH值
  * 入口参数：无
  * 返回参数：pH值（0-14）
  * 说明：使用PA1（ADC_Value[1]）采集pH传感器模拟量
  *       电压转pH值公式：pH = -5.6342 * V + 16.413
  */
float GatePH_GetData(void)
{
	float PH_Value;
	float voltage;
	float TempData = 0;
	
	// 采集20次求平均值，增强稳定性
	for(uint8_t i = 0; i < 20; i++)
	{
		TempData += AD_Value[1];  // PA1对应ADC_Value[1]
		DelayXms(5);
	}
	
	// 计算平均值
	TempData = TempData / 20;
	
	// ADC转换为电压：12位分辨率，3.3V参考电压
	voltage = (TempData / 4095.0) * 3.3;
	
	// 电压转pH值（线性拟合）
	PH_Value = -5.6342 * voltage + 16.413;
	
	// 限制范围在0-14之间
	if(PH_Value < 0)
		PH_Value = 0;
	if(PH_Value > 14.0)
		PH_Value = 14.0;
	
	return PH_Value;
}
