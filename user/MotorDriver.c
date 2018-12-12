#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "misc.h"

#include "MotorDriver.h"


uint32_t task_Run_couter=0;
uint8_t  task_Run_flag=0;

uint32_t Motor_Run_couter=0;
uint8_t  Motor_Run_flag=0;

uint8_t  Motor_Direction_flag=0; //0 -> -, 1->+


void TurnDownMotro(void)
{
	GPIO_WriteBit(Motor_R_PORT, Motor_R_PIN, Bit_SET);
	GPIO_WriteBit(Motor_L_PORT, Motor_L_PIN, Bit_RESET);
}

void TurnUpMotro(void)
{
	GPIO_WriteBit(Motor_R_PORT, Motor_R_PIN, Bit_RESET);
	GPIO_WriteBit(Motor_L_PORT, Motor_L_PIN, Bit_SET);
}

void TurnOFFMotro(void)
{
	GPIO_WriteBit(Motor_R_PORT, Motor_R_PIN, Bit_RESET);
	GPIO_WriteBit(Motor_L_PORT, Motor_L_PIN, Bit_RESET);
}

void MotorDriverGPIO_Init(void)
{
	    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(Motor_R_RCC, ENABLE);
		RCC_APB2PeriphClockCmd(Motor_L_RCC, ENABLE);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = Motor_R_PIN;
    GPIO_Init(Motor_R_PORT, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin = Motor_L_PIN;
    GPIO_Init(Motor_L_PORT, &GPIO_InitStructure);
}

void TIM4_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;                                            
         
	TIM_DeInit(TIM4);
	//TIM_InternalClockConfig(TIM4);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = 1000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 48-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseInitStructure);

	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);  
		
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                           
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 100;                 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 100;                        
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                 
	NVIC_Init(&NVIC_InitStructure);  
	
}


void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
    {
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
				task_Run_couter++;
				Motor_Run_couter++;
				if(task_Run_couter % 1000==0)  //1000ms
				{
					task_Run_couter = 0;
					task_Run_flag = 1;
				}
				if((Motor_Run_couter % 2000==0) && Motor_Run_flag)//电机运行时间
				{
					Motor_Run_couter = 0;
					Motor_Run_flag = 0;
				}
		}
}

void MotorControlFunc(void)
{
	if(Motor_Run_flag && Motor_Direction_flag)
		TurnDownMotro();
	else if(Motor_Run_flag && Motor_Direction_flag==0)
		TurnUpMotro();
	else
		TurnOFFMotro();
	
}

