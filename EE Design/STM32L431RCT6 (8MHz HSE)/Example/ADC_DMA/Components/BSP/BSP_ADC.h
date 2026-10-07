#ifndef _DSP_ADC_H_
#define _DSP_ADC_H_
#include "main.h"

#define ADC_CONVERTED_DATA_BUFFER_SIZE   ((uint32_t)  32)   /* Size of array aADCxConvertedData[] */

extern __IO uint16_t AdcValue;
extern ALIGN_32BYTES (uint16_t   aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE]);


void DSP_AdcStart(void);

#endif
