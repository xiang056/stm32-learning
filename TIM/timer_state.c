/*
## 功能特點

-  **多任務調度**：1ms/10ms/100ms 三級時間片任務
-  **按鈕防抖動**：20ms 硬體防抖動演算法
-  **狀態機控制**：三態循環切換 (IDLE → RUN → STOP)
-  **LED 狀態指示**：
  - PD12: 100ms 心跳燈
  - PD13: IDLE 狀態指示  
  - PD14: RUN 狀態指示
  - PD15: STOP 狀態指示

*/


#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "button.h"
#include "tim.h"



void SystemClock_Config(void){}

//volatile uint32_t tick_1ms = 0;
void Task_1ms(void) ;                                     
void Task_10ms(void);
void Task_100ms(void);

volatile uint8_t flag_1ms = 0;
volatile uint8_t flag_10ms = 0;
volatile uint8_t flag_100ms = 0;


static uint8_t  key_state = 0;
static uint8_t  key_counter = 0;

void Task_1ms(void)
{
    uint8_t raw = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    
    if(raw == GPIO_PIN_RESET)  //按下
    {
        if(key_counter < 20 )    //抖動20ms
          key_counter++;
        
        if(key_counter >= 20 )
          key_state= 1;               //確認按下
    }
    
    else                          //放開
    {
        if(key_counter > 0)      
          key_counter--;
        
        if(key_counter == 0)
          key_state = 0;               //確認放開
      
    }
}



typedef enum{
             STATE_IDLE,
             STATE_RUN,
             STATE_STOP
}SystemState;
            
static SystemState sys_state = STATE_IDLE;

void Task_10ms(void)
{
  uint8_t static last_key_press = 0;
  
  uint8_t key_press_event = 0;
  
  if(key_state == 1 && last_key_press == 0)
  {
      key_press_event = 1;
  }
  
  last_key_press = key_state;
  
  
  
  
  switch(sys_state)
  {
  case STATE_IDLE:
    if(key_press_event)
    {
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
      sys_state = STATE_RUN;
    }

    break;
    
  case STATE_RUN:
    if(key_press_event)
    {
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
      sys_state = STATE_STOP;
    }
    break;
    
  case STATE_STOP:
    if(key_press_event)
    {
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
      sys_state = STATE_IDLE;
    }
    break;
    
  }
}
  

void  Task_100ms(void)
{
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}
    

  



int main(void)
{
    HAL_Init();
    SystemClock_Config();
    
    GPIO_Init_All();            
    Button_Init();
    TIM2_Init();
    
    HAL_TIM_Base_Start_IT(&htim2);   //1ms tick start
   

    while (1)
    {
        //任務A 每1ms
        if(flag_1ms)
        {
          flag_1ms = 0;  
          Task_1ms();
        }                    
        
        // 任務B 每10ms
        if(flag_10ms)
        {
          flag_10ms = 0;  
          Task_10ms();
        }
        
        //任務C 每100ms
        if(flag_100ms)
        {
          flag_100ms = 0;  
          Task_100ms();
        }     
    }
}






void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint8_t  cnt10 = 0;
    static uint8_t  cnt100 = 0;
  
    if(htim->Instance == TIM2)
    {
        flag_1ms = 1;
        
        if(++cnt10 >= 10)
        {
            cnt10 = 0;
            flag_10ms = 1;
        }
      
        if(++cnt100 >= 100 )
        {
            cnt100 = 0;
            flag_100ms = 1;
          
        }
    }  
}

