#include "stm32f4xx_hal.h"
#include "gpio.h"


void SystemClock_Config(void){}
void GPIO_Init_All(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_Init_All();            
    
    uint8_t btn_now = 0;
    uint8_t btn_last = 0;
    uint8_t state = 0;

    while (1)
    {
      btn_now = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
      
      if(btn_now == GPIO_PIN_SET && btn_last == GPIO_PIN_RESET)
      {
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
          state++;
          if(state > 3)
          {
            state = 0;
          } 
            
           switch(state)                                                                      
           {
           case 0:
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                  break;
                    
           case 1:
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                  break;
                    
                    
           case 2:         
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);                    
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
                  break;
           case 3:
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                  break;
           }
           
             
          
          
          
        } 
        
      }      
        btn_last =btn_now;
}

}