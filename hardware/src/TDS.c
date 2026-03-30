
#include "stm32f10x.h"
#include "TDS.h"
#include "AD.h"
#include "delay.h"
#include "ds18b20.h"
 float water_temp1; 
float GateTDS_GetData_PPM(void)
{
	float TDS;
	float TempData;
	float T1,T2;
	float V;
	//float TDS;
	for(uint8_t i=1;i<20;i++)
	{
		TempData+=AD_Value[0];
		DelayXms(5);
	}
	TempData=TempData/20;
	water_temp1=DS18B20_Get_Temp()/10.0f;
	T1 = water_temp1;
	T2=1+0.02*(T1-25);
	V=(((TempData/4095.0)*3.3)*T2);
	TDS=66.71*V*V*V-127.93*V*V+428.7*V;
	return TDS;
//	TDS=(TempData/4095.0)*3.3;
//	TDS=66.71*TDS*TDS*TDS-127.93*TDS*TDS+428.7*TDS;
//	return TDS;
}

