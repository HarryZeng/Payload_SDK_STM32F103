 
#include "stm32f10x.h" 
#include "stm32f10x_tim.h" 
#include "GUA_Timer1_PWM.h"  
  
/*********************************************/    

#define GUA_TIMER1_PWM_PORT             GPIOA  
#define GUA_TIMER1_PWM_PIN              GPIO_Pin_8|GPIO_Pin_9  
#define GUA_TIMER1_PWM_MODE             GPIO_Mode_AF_PP 
#define GUA_TIMER1_PWM_GPIO_CLOCK				RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO 
#define GUA_TIMER1_PWM_PERIPH_CLOCK			RCC_APB2Periph_TIM1 
 

#define GUA_Timer1_PWM_Prescaler						(48 - 1)  
 
/*********************************************/  
static void GUA_Timer1_PWM_IO_Init(void);
static void GUA_Timer1_PWM_Config_Init(GUA_U16 GUA_TIMER1_PWM_PERIOD);
 

static void GUA_Timer1_PWM_IO_Init(void)  
{      
 
	GPIO_InitTypeDef GPIO_InitStructure;  
 

	RCC_APB2PeriphClockCmd(GUA_TIMER1_PWM_GPIO_CLOCK, ENABLE);	
 

	GPIO_InitStructure.GPIO_Pin = GUA_TIMER1_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GUA_TIMER1_PWM_MODE;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GUA_TIMER1_PWM_PORT, &GPIO_InitStructure);		
}
 
                    
//******************************************************************************  
static void GUA_Timer1_PWM_Config_Init(GUA_U16 GUA_TIMER1_PWM_PERIOD)  
{      
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
	TIM_OCInitTypeDef  TIM_OCInitStructure;  
  

	RCC_APB2PeriphClockCmd(GUA_TIMER1_PWM_PERIPH_CLOCK, ENABLE);  
	

	TIM_TimeBaseStructure.TIM_Period = GUA_TIMER1_PWM_PERIOD;								
	TIM_TimeBaseStructure.TIM_Prescaler = GUA_Timer1_PWM_Prescaler;		
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;														
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;									 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;					

	TIM_OCInitStructure.TIM_Pulse = 1500;																			 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;							
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;					
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = 1500;																			 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;							
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);																     
 

	GUA_Timer1_PWM_Status(GUA_TIMER1_PWM_STATUS_OFF);	
	

	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);											
	TIM_ARRPreloadConfig(TIM1, ENABLE);																				
	TIM_Cmd(TIM1, ENABLE);																									
}
 
                  
//******************************************************************************    
void GUA_Timer1_PWM_Status(GUA_U8 nGUA_Timer1_PWM_Status)  
{  
  if(nGUA_Timer1_PWM_Status == GUA_TIMER1_PWM_STATUS_ON)  
  {   
		TIM_SetCounter(TIM1, 0);		
		TIM_CtrlPWMOutputs(TIM1, ENABLE);			
  }  

  else  
  {  
		TIM_CtrlPWMOutputs(TIM1, DISABLE);	 	
  }  
}  
  
                        
//******************************************************************************    
void GUA_Timer1_PWM_SetDutyCycle(GUA_16 nGUA_Timer1_PWM_DutyCycle,uint8_t CH)  
{  
	if(CH ==1 )
		TIM_SetCompare1(TIM1, nGUA_Timer1_PWM_DutyCycle);
		//TIM_SetCompare1(TIM1, GUA_TIMER1_PWM_PERIOD*nGUA_Timer1_PWM_DutyCycle/100);   
	else if(CH==2)
		TIM_SetCompare2(TIM1, nGUA_Timer1_PWM_DutyCycle);  
}  
  
                     
//******************************************************************************    
void GUA_Timer1_PWM_Init(GUA_U16 nGUA_TIMER1_PWM_PERIOD)   
{  	

	GUA_Timer1_PWM_IO_Init();  
 

	GUA_Timer1_PWM_Config_Init(nGUA_TIMER1_PWM_PERIOD);
}  
