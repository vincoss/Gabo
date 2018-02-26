/*
 * main.c
 *
 * Created: 08/02/2018
 * Author : Ferdinand Lukasak
 
	 Copy main.hex into Arduino board use this command
	 1. Open command prompt
	 2. cd {SolutionDir}\debug
	 3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex
	 4. avrdude -p atmega328p -c arduino -P COM6 -b 57600 -D -U flash:w:main.hex
 */ 

#include <string.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "Usart.h"
#include "Adc.h"
#include "GaboIo.h"
#include "GaboUsart.h"
#include "GaboCommand.h"
#include "GaboTime.h"


int main(int argc, char *argv[])
{
	UsartInitialize();
	GaboUsartInterruptInitialize();
	GaboTimeIninialize();

	MainLoop();

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

void GaboCommandWriteLog(const char * message)
{
	if (message == NULL || strlen(message) <= 0)
	{
		return; // Nothing
	}
	
	UsartWriteCharString(message);
	UsartWriteChar('\r\n');
}

#pragma endregion GaboCommand implementation

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

#pragma region MainLoop implementation

volatile uint8_t _mainLoopOnUpdateRunning;

void MainLoop(void)
{
	const int ticksPerSecond = 25;
	const int skipTicks = 1000 / ticksPerSecond;
	const int maxFrameSkip = 5;

	unsigned long long int nextGameTick = GaboTimeGetTickCount();

	while (1)
	{
		int loops = 0;

		while (GaboTimeGetTickCount() > nextGameTick && loops < maxFrameSkip)
		{
			MainLoopOnUpdate();

			nextGameTick += skipTicks;
			loops++;
		}

		// Usage view_position = position + (speed * interpolation)
		float interpolation = (GaboTimeGetTickCount() + skipTicks - nextGameTick) / (float)skipTicks;
		MainLoopOnRender(interpolation);
	}
}

void MainLoopOnUpdate(void)
{
	if(_mainLoopOnUpdateRunning == 1)
	{
		return;
	}
	_mainLoopOnUpdateRunning = 1;
	
	/*
		NOTE: Order is important.
		
		Highest priority
		
		*Read sensors
		*Read commands
		*Calculate
		*Push commands and calc values
	*/
	
	GaboCommandRead();
	
	/*
		Lowest priority.
	*/
	
	_mainLoopOnUpdateRunning = 0;
}

void MainLoopOnRender(float interpolation)
{
	// TODO: here possible read sensors or other, but it might run too fast.
}

#pragma endregion MainLoop implementation