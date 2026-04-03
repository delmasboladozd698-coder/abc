#include "motor.h"

/**
  * @brief  ?? PWM ??? (??????????,????PWM)
  * @note   ?? PB7 (TIM4_CH2) ????
  * @param  arr: ??????
  * @param  psc: ??????
  */
void Motor_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    // 1. ????:?? TIM4,GPIOB ???? AFIO
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    // 2. ?? GPIO: ??? PB7 (??????,???? PWM)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // ??????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 3. ?????? TIM4 ????
    TIM_TimeBaseStructure.TIM_Period = arr;            // ????????????
    TIM_TimeBaseStructure.TIM_Prescaler = psc;         // ????
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;       // ????
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ??????
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    // 4. (?? PB6 - TIM4_CH1 ? PWM ??????)

    // 5. ?? TIM4 ??2 (?? PB7 - ??) ? PWM ??
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;                 // ?????? 0 (??)
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    // 6. ?????
    TIM_Cmd(TIM4, ENABLE);
}

/**
  * @brief  ?????? (?? PB7 ?? PWM ???)
  * @param  speed: ???? (0 ~ arr)
  */
void Set_Pump_Speed(u16 speed)
{
    TIM_SetCompare2(TIM4, speed); // ?? TIM4_CH2 ????
}