/*
 * Adc.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand
 */ 


#ifndef ADC_H_
#define ADC_H_


#include <stdlib.h>
#include <avr/io.h>

/// Initialize Adc channel
void AdcInitialize(void);

/// Read ADC channel.
/// Channel number between 0-7
/// Return value between 0-1023
uint16_t AdcRead(uint8_t channel);


#endif /* ADC_H_ */