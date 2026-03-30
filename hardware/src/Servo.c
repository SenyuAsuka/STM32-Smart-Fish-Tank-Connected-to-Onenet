#include "stm32f10x.h"                  // Device header

#include "PWM.h"



/**

  * 函    数：舵机初始化

  * 参    数：无

  * 返 回 值：无

  */

void Servo_Init(void)

{

PWM_Init(); // 初始化舵机的底层PWM

}



/**

  * 函    数：舵机设置角度

  * 参    数：Angle 要设置的舵机角度，范围：0~180

  * 返 回 值：无

  * 说    明：

  * 标准SG90脉宽范围通常为: 500us - 2500us (对应 0-180度)

  * 原代码的 1000-2000us 可能会导致转动角度偏小

  */

void Servo_SetAngle(float Angle)

{

    // 1. 安全限幅：防止传入非法角度导致舵机过载

    if (Angle > 180) Angle = 180;

    if (Angle < 0) Angle = 0;



    // 2. 计算PWM值 (假设ARR=20000, PSC=71 => 1个单位=1us)

    // 方案A (推荐)：标准SG90范围 (0度=500us, 180度=2500us)

    // 这种计算方式能让舵机真正转满 180 度

    uint16_t compareValue = (uint16_t)(Angle / 180.0f * 2000.0f + 500.0f);

    

    /* // 方案B：如果你测试发现方案A转得太多导致卡住，可以用回原来的窄范围 (0度=1000us, 180度=2000us)

    uint16_t compareValue = (uint16_t)(Angle / 180.0f * 1000.0f + 1000.0f);

    */



PWM_SetCompare3(compareValue); // 设置占空比 (连接 TIMx_CH3)

}
