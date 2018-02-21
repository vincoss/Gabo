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
	GaboUsartInterruptInitialize();
	
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
	if (message == NULL || strlen(message) <= 0)
	{
		return; // Nothing
	}
	
	char buffer[strlen(message) + 1];
	itoa(message, buffer, 10);
	UsartWriteCharString(message);
	UsartWriteChar('\r\n');
}

#pragma endregion GaboCommand implementation


volatile uint8_t _mainLoopTimerEvent;
volatile uint8_t _mainLoopTimerEventRunning;

#pragma region GaboTime (timer) implementation

void GaboTimeIninialize(void)
{
	// Reset ticks
	GaboTimeTickCount = 0;
	
	// TODO: review the timer logic, why timer1 not timer 2???
	cli();		// Disable global interupts

	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B

	TCNT1 = 0;		// initialize counter
	OCR1A = 0xF9;	// Fire every 1ms, Run at TODO??? Hz

	// Prescaler 64 TODO: set prescaller to 1
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);

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

void MainLoop(void)
{
	const int ticksPerSecond = 25;
	const int skipTicks = 1000 / ticksPerSecond;
	const int maxFrameSkip = 5;

	unsigned long long nextGameTick = GaboTimeGetTickCount();

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
	if(_mainLoopTimerEventRunning == 1)
	{
		return;
	}
	_mainLoopTimerEventRunning = 1;
	UsartWriteCharString("MainLoopOnUpdate");
}

void MainLoopOnRender(float interpolation)
{
	UsartWriteCharString("MainLoopOnRender");
	
	char buffer[5];
	GaboCommandWriteLog(IntToString(interpolation, "%f", buffer, sizeof buffer));
}

#pragma endregion MainLoop implementation

//void SetupTimer(void)
//{
//_mainLoopTimerEvent = 0;
//_mainLoopTimerEventRunning = 0;
//
//// TODO: review the timer logic, why timer1 not timer 2???
//cli();		// Disable global interupts
//
//TCCR1A = 0;     // set entire TCCR1A register to 0
//TCCR1B = 0;     // same for TCCR1B
//
//TCNT1 = 0;		// initialize counter
//OCR1A = 0x30D3;	// Fire every 50ms, Run at 20Hz
//
//// Prescaler 64
//TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
//
//// enable compare interrupt
//TIMSK1 |= (1 << OCIE1A);
//
//sei();	// enable global interrupts
//}

//// ISR is fired whenever a match occurs
//ISR(TIMER1_COMPA_vect)
//{
//if (_mainLoopTimerEventRunning == 1)
//{
//// NOTE: Timer event is still not completed skip current event.
//return;
//}
//
//_mainLoopTimerEvent = 1;
//}

// TODO: previous loop, just for reference, remove
//while (1)
	//{
		//if(_mainLoopTimerEventRunning == 1)
		//{
			//continue;
		//}
		//
		//if (_mainLoopTimerEvent == 1)
		//{
			//_mainLoopTimerEventRunning = 1;
			//
			///*
				//Read sensors
				//Read commands
				//Calculate
				//Push commands and calc values
			//*/
			//
			//// NOTE: order these by importance. Highest
			//GaboCommandRead(); // Each loop attempt to read the input commands.
					//
			//// Lowest priority
			//
			//
			//_mainLoopTimerEvent = 0;
			//_mainLoopTimerEventRunning = 0;
		//}
	//}