#include "tim.h"

TIM_HandleTypeDef htim2;

void TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();   // ★★★ 必要：開啟 TIM2 時鐘

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 16000 - 1; 
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1000 - 1;       
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim2);

    // ★★★ 必要：告訴 NVIC 要處理 TIM2 中斷
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    // ★★★ 啟動中斷模式的 Timer
    HAL_TIM_Base_Start_IT(&htim2);
}
