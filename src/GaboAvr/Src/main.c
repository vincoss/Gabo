/*
 * main.c
 *
 * Created: 08/02/2018
 * Author : Ferdinand Lukasak
 
	 Copy main.hex into Arduino board use this command
	 1. Open command prompt
	 2. cd {SolutionDir}\debug
	 3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex
 */ 

#include <string.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "Usart.h"
#include "Adc.h"
#include "GaboIo.h"
#include "GaboUsart.h"
#include "GaboCommand.h"


volatile uint8_t _timerEvent;
volatile uint8_t _timerEventRunning;

int main(int argc, char *argv[])
{
	UsartInitialize();
	GaboUsartInterruptInitialize();
	SetupTimer(); // Start last after other sensors and registers are initialized.

	while (1)
	{
		if (_timerEvent == 1)
		{
			// NOTE: order these by importance. Highest
			GaboCommandRead(); // Each loop attempt to read the input commands.
					
			// Lowest priority
			
			
			_timerEvent = 0;
			_timerEventRunning = 0;
		}
	}

	return 0;
}

#pragma region GaboCommand implementation

void GaboCommandCopy(char * srcData, char * destCommand)
{
	if (strlen(srcData) <= 0)
	{
		return;
	}

	// The USART might interrupt this - don't let that happen!
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		// Copy the contents of data_in into command_in
		memcpy(destCommand, srcData, 8);

		//// Now clear data_in, the USART can reuse it now
		memset(srcData, 0, 8);
	}
}

void GaboCommandWriteLog(char * message)
{
	if (strlen(message) <= 0)
	{
		return 0;
	}
	
	char buffer[strlen(message) + 1];
	itoa(message, buffer, 10);
	UsartWriteCharString(message);
	UsartWriteChar('\r\n');
}

#pragma endregion GaboCommand implementation

#pragma region Timer methods

void SetupTimer(void)
{	
	_timerEvent = 0;
	_timerEventRunning = 0;

	// TODO: review the timer logic, why timer1 not timer 2???
	cli();		// Disable global interupts

	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B

	TCNT1 = 0;		// initialize counter
	OCR1A = 0x30D3;	// Fire every 50ms, Run at 20Hz

	// Prescaler 64
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

	// enable compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei();	// enable global interrupts
}

// ISR is fired whenever a match occurs
ISR(TIMER1_COMPA_vect)
{
	if (_timerEventRunning == 1)
	{
		return;
	}

	_timerEvent = 1;
	_timerEventRunning = 1;
}

#pragma endregion