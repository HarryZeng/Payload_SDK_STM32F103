#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "ADC.h"

float ADC_value=0;


void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE );	  //使能ADC1通道时钟
		//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}

void Adc1_Init(void)  
{     

  ADC_InitTypeDef  ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);   //设置ADC分频因子6 64M/8=8,ADC最大时间不能超过14M
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular configuration */ 

	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_7Cycles5);

   //ADC_DMACmd(ADC1 , ENABLE);
   //ADC_ExternalTrigConvCmd(ADC1, ENABLE);
  
   ADC_Cmd(ADC1 , ENABLE);   
   ADC_ResetCalibration(ADC1);
   while(ADC_GetResetCalibrationStatus(ADC1)){};
   ADC_StartCalibration(ADC1);
   while(ADC_GetCalibrationStatus(ADC1)){};

}     

void ADCinit(void)
{
	ADC1_GPIO_Config();
	Adc1_Init();
}


uint16_t Get_Adc(void)   
{
      //指定ADC规则组通道,一个序列,采样时间                   
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);        //使能指定的ADC1软件转换启动功能    
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
    return ADC_GetConversionValue(ADC1);           //返回ADC1的转换结果
}
