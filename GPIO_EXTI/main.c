#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "button.h"

void SystemClock_Config(void){}
void GPIO_Init_All(void);
void Button_Init(void);



volatile uint8_t btn_press_event = 0; //按下事件
volatile uint8_t btn_release_event = 0; //放開事件
volatile uint8_t state = 0;
volatile uint32_t press_time = 0;//紀錄按下時間
volatile uint32_t release_time = 0;//紀錄鬆開時間
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_Init_All();            
    Button_Init();
    
   

    while (1)
    {
      uint32_t now = HAL_GetTick();
      
      uint8_t press = btn_press_event;
      if(press)
      {
         btn_press_event = 0;         
         press_time = now;       
      }
      
      uint8_t release = btn_release_event;
      if(release)
      {
         btn_release_event = 0;         
         release_time = now;
        
         uint32_t p = press_time;
         uint32_t r = release_time;
         uint32_t duration = r - p;
         
         if(duration < 500)
         {
              //短按event

             HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
             HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
             
             ++ state;
             
             if(state > 4)
               state = 0;
             
             switch (state)
             {
             case 0:
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
                break;

             case 1:
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
                break;

             case 2:
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
                break;

             case 3:
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
                break;
             case 4:
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
                break;                
             }
             
             
             
         }
         else
         {
              //長按event
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
           
              
         }
      }
    }
}




    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
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