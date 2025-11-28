#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "button.h"

void SystemClock_Config(void){}
void GPIO_Init_All(void);
void Button_Init(void);



volatile uint8_t btn_event = 0;    //事件flag
uint32_t last_press_time = 0;      //上次按下時間
uint8_t state = 0;

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_Init_All();            
    Button_Init();
    
   

    while (1)
    {
        if(btn_event == 1)
        {
          btn_event = 0;
          
          uint32_t now = HAL_GetTick();
          
          if(now - last_press_time > 20)
          {
             last_press_time = now;
             state ++;
             
             if(state > 3 )
               state = 0;
             
             
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
        
    }
   
}




    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
      {  
         if(GPIO_Pin == GPIO_PIN_0)
         {
           btn_event = 1;
           
         }
        
        
     
      }