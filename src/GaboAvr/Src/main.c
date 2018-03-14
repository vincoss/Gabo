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
#include "GaboSpi.h"
#include "GaboLoop.h"

int main(int argc, char *argv[])
{
	InitializeDefaults();
	UsartInitialize();
	GaboUsartInterruptInitialize(); // TODO: migrate to Usart.h
	GaboTimeIninialize();
	GaboSpiInitialize();

	GaboLoopMain();

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

#pragma region GaboLoop implementation

volatile uint8_t _gaboLoopOnUpdateRunning;

void GaboLoopMain(void)
{
	const int ticksPerSecondMs = 1;	// Run very fast, every 1ms
	const int ticksPerSecond = 25;	// Run 25 times per second.
	const int skipTicks = 1000 / ticksPerSecond;
	const int maxFrameSkip = 5;

	unsigned long long int nextGameTick = GaboTimeGetTickCount();

	while (1)
	{
		int loops = 0;

		while (GaboTimeGetTickCount() > nextGameTick && loops < maxFrameSkip)
		{
			GaboLoopOnUpdate();

			nextGameTick += skipTicks;
			loops++;
		}

		// Usage view_position = position + (speed * interpolation)
		float interpolation = (GaboTimeGetTickCount() + skipTicks - nextGameTick) / (float)skipTicks;
		GaboLoopOnRender(interpolation);
	}
}

void GaboLoopOnUpdate(void)
{
	if(_gaboLoopOnUpdateRunning == 1)
	{
		return;
	}
	_gaboLoopOnUpdateRunning = 1;
	
	/*
		NOTE: Order is important.
		
		Highest priority
		
		*Read commands
		*Read sensors
		*Calculate
		*Push commands and calc values
	*/
	
	GaboCommandRead();
	
	// Do not execute inf input commands are incomming or processing.
	if(startWriteCommand == 0)
	{
		ProcessOutputBus();
	}
	
	/*
		Lowest priority.
	*/
	
	_gaboLoopOnUpdateRunning = 0;
}

void GaboLoopOnUpdateMs(void)
{
	// TODO: check if can already read
	ProcessInputBus();
}

void GaboLoopOnRender(float interpolation)
{
	// TODO: here possible read sensors or other, but it might run too fast.
}

#pragma endregion GaboLoop implementation

uint8_t ReadInputBus()
{
	
	
}

void ProcessInputBus()
{
	uint8_t value = ReadInputBus();	
}

void ProcessOutputBus()
{
	uint8_t flag = 0;
	
	if(PowerCommand != powerCommandTemp)
	{
		PowerCommand = powerCommandTemp;
		flag = 1;
	}
	
	if(PowertrainCommand != powertrainCommandTemp)
	{
		PowertrainCommand = powertrainCommandTemp;
		flag = 1;
	}
	
	if(flag || (IsOutputInitialized == 0)) // Push into bus, only if changed or if is the first time.
	{
		GABOIO_SPI_SET_OUTPUT_LATCH_LOW;
		
		GaboSpi_Send(PowerCommand);
		GaboSpi_Send(PowertrainCommand);
		// More commands here
		
		GABOIO_SPI_SET_OUTPUT_LATCH_HIGH;
		
		IsOutputInitialized = 1;
	}
}

void InitializeDefaults()
{
	IsOutputInitialized = 0;
	GABOIO_SPI_SET_OUTPUT_LATCH_HIGH;
	GABOIO_SPI_SET_INPUT_LATCH_HIGH;
}