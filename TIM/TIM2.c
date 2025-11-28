#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "button.h"

void SystemClock_Config(void){}
void GPIO_Init_All(void);
void Button_Init(void);
void TIM2_Init(void);

                                       

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_Init_All();            
    Button_Init();
    TIM2_Init();
   

    while (1)
    {
      
    }
}




   /* void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
      {  
         if(GPIO_Pin == GPIO_PIN_0)
         {
           GPIO_PinState pin = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
             
             if(pin == GPIO_PIN_SET)
             {
                btn_press_event = 1; //紀錄按下事件
             }
             else
             {
               
               btn_release_event = 1; //記錄放開事件
             }           
         }        
      }
  */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        // 每一秒翻轉 LED
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    }
}
