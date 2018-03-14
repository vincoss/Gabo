/*
 * GaboTime.c
 *
 * Created: 14/03/2018 5:17:26 PM
 *  Author: Ferdinand Lukasak
 */ 

#include <avr/interrupt.h>
#include "GaboTime.h"

#pragma region GaboTime (timer) implementation

void GaboTimeIninialize(void)
{
	// Reset ticks
	GaboTimeTickCount = 0;
	
	cli();	// Disable global interrupts

	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B

	TCNT1 = 0;		// initialize counter
	OCR1A = 0x3E7F;	// Fire every 1ms, run at 1000Hz

	// Reset, waveform and prescaler
	TCCR1B &= ~(WGM12 | CS12 | CS11 | CS10);
	
	// Set waveform and prescaler to 1
	TCCR1B |= (1 << WGM12) | (1 << CS10);

	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei();	// enable global interrupts
}

// ISR is fired whenever a match occurs
ISR(TIMER1_COMPA_vect)
{
	GaboTimeTickCount++;
}

#pragma endregion
