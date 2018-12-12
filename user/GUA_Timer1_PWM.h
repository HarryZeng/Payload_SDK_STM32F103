//******************************************************************************                            
//name:             GUA_Timer1_PWM.h               
//introduce:        ???1?PWM??????        
//author:           ??????                     
//email:            897503845@qq.com         
//QQ group          ??????STM8/STM32(164311667)                      
//changetime:       2017.01.14     
//******************************************************************************    
#ifndef _GUA_TIMER1_PWM_H_  
#define _GUA_TIMER1_PWM_H_  
   
/*********************???************************/       
//???
#ifndef GUA_U8        
typedef unsigned char GUA_U8;        
#endif    
 
#ifndef GUA_8        
typedef signed char GUA_8;        
#endif      
      
#ifndef GUA_U16        
typedef unsigned short GUA_U16;        
#endif 
 
#ifndef GUA_16        
typedef signed short GUA_16;        
#endif         
      
#ifndef GUA_U32        
typedef unsigned long GUA_U32;        
#endif 
 
#ifndef GUA_32        
typedef signed long GUA_32;       
#endif
 
#ifndef GUA_U64    
typedef unsigned long long GUA_U64;  
#endif
 
#ifndef GUA_64    
typedef signed long long GUA_64;  
#endif
 
//PWM????  
#define GUA_TIMER1_PWM_STATUS_ON                0       //PWM??  
#define GUA_TIMER1_PWM_STATUS_OFF               1       //PWM??  
 
/*********************??????************************/   
void GUA_Timer1_PWM_Status(GUA_U8 nGUA_Timer1_PWM_Status);  
void GUA_Timer1_PWM_SetDutyCycle(GUA_16 nGUA_Timer1_PWM_DutyCycle, uint8_t CH);  
void GUA_Timer1_PWM_Init(GUA_U16 nGUA_Timer1_PWM_Prescaler);  
  
#endif  
