#include "adc.h"

void LMT_Init(){
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 50);
}

void LMT_DeInit(){
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
    HAL_ADC_Stop(&hadc1);
}

uint16_t LMT_GetValue(){
    uint16_t ADC2_Value;
    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
        ADC2_Value = HAL_ADC_GetValue(&hadc1);
    }
    return ADC2_Value;
}

uint8_t LMT_GetTemp(){
    //HAL_ADC_Stop(&hadc1);
    uint16_t raw = LMT_GetValue();
    uint8_t temp = -0.193*(raw/4096.0*3300)+212.009;
    //HAL_ADC_Start(&hadc1);
    return temp;
}

int32_t get_volt(uint32_t num)
{
    int32_t temp;
    temp = num;
    temp <<= 8;
    temp >>= 8;
    return temp;
}
// Created by umbor on 10/8/2020.
//

