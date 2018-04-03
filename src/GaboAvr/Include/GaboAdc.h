/*
 * GaboAdc.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_ADC_H_
#define GABO_ADC_H_


#include <avr/io.h>

/// Initialize Adc channel
void GaboAdcInitialize(void);

/// Read ADC channel.
/// Channel number between 0-7
/// Return value between 0-1023
uint16_t GaboAdcRead(uint8_t channel);


#endif /* GABO_ADC_H_ */