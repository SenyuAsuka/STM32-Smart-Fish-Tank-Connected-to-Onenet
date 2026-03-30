#ifndef _DELAY_H_
#define _DELAY_H_
#define delay_us DelayUs
#define delay_ms DelayMs






void Delay_Init(void);

void DelayUs(unsigned short us);

void DelayXms(unsigned short ms);

void DelayMs(unsigned short ms);

#endif
