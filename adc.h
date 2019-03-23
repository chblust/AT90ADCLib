#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void initADC( uint8_t prescale );

void startADCAutoTrigger();

uint16_t adcRead( uint8_t channel );

#endif // ADC_H