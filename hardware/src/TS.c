#include "stm32f10x.h"
#include "TS.h"
#include "AD.h"
#include "delay.h"
#include "ds18b20.h"
	float water_temp2; 
	float GateTS_GetData_NTU(void)
{
	float TS;
	float TempData;
	float T;
	float V;
	for(uint8_t i=1;i<20;i++)
	{
		TempData+=AD_Value[1];
		DelayXms(5);
	}
	TempData=TempData/20;
	water_temp2=DS18B20_Get_Temp()/10.0f;
	
	T=-0.0192*(T-25);
//	TS=((TempData/4095.0)*3.3);
	
	TS=(TempData/4095.0)*3.3;
	//TS=-865.68*(TS-T)+2856.77-558;
	//TS=-865.68*TS+2856.77-142;
	TS=-887.1*TS+2853.5;
	return TS;

}

