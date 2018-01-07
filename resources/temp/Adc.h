
#ifndef ADC_H
#define ADC_H

#include <stdlib.h> 
#include <avr/io.h>	

/// Initialize Adc channel
void AdcInitialize(void);

/// Read ADC channel. 
/// Channel number between 0-7
/// Return value between 0-1023
uint16_t AdcRead(uint8_t channel);

#endif