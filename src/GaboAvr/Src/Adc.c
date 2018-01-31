/*
 * Adc.c
 *
 * Created: 29/01/2018 10:10:12 PM
 *  Author: Ferdinand Lukasak
 */ 

#include <avr/io.h>
#include "Adc.h"

// Initialize the ADC Module
void AdcInitialize(void)
{
	ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); // 16Mhz/128 = 125Khz the ADC reference clock
	ADMUX |= (1 << REFS0); // Voltage reference from Vref=AVcc
	ADCSRA |= (1 << ADEN); // Turn on ADC
	ADCSRA |= (1 << ADSC); // Do an initial conversion because this one is the slowest and to ensure that everything is up and running
}

// Read ADC value
uint16_t AdcRead(uint8_t channel)
{
	// Select ADC Channel ch must be 0-7
	channel = channel & 0b00000111;

	ADMUX &= 0xF0;                  // Clear the older channel that was read
	ADMUX |= channel;               // Defines the new ADC channel to be read
	ADCSRA |= (1 << ADSC);          // Starts a new conversion
	while (ADCSRA & (1 << ADSC));   // Wait until the conversion is done
	return ADCW;                    // Returns the ADC value of the chosen channel
}
