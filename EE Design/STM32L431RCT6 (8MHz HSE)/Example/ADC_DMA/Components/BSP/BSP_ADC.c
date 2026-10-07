/**
  ****************************(C) COPYRIGHT 2021 Boring_TECH*********************
  * @file       DSP_adc.c/h
  * @brief      ADC DMA相关函数	
  * @note      	
  * @history
  *  Version    Date            Author          Modification
  *  V3.0.0     2020.7.14     	              	1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2021 Boring_TECH*********************
  */
#include "BSP_adc.h"
#include "adc.h"

__IO uint16_t AdcValue = 0;

ALIGN_32BYTES (uint16_t   aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]);

/**
  * @brief  Conversion complete callback in non-blocking mode
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
  /* Invalidate Data Cache to get the updated content of the SRAM on the first half of the ADC converted data buffer: 32 bytes 
		 使数据缓存无效，以便在ADC转换数据缓冲区的下半部分获得SRAM的更新内容:32字节*/ 
  SCB_InvalidateDCache_by_Addr((uint32_t *) &aADCxConvertedData[0], ADC_CONVERTED_DATA_BUFFER_SIZE);
}

/**
  * @brief  Conversion DMA half-transfer callback in non-blocking mode
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
   /* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer: 32 bytes */ 
  SCB_InvalidateDCache_by_Addr((uint32_t *) &aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE/2], ADC_CONVERTED_DATA_BUFFER_SIZE);
}

/**
  * @brief  使能ADC DMA读取
  * @param  none
  * @retval None
  */
void DSP_AdcStart(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);

	HAL_ADC_Start_DMA(&hadc1,
													(uint32_t *)&aADCxConvertedData,
													ADC_CONVERTED_DATA_BUFFER_SIZE
												 );
}









