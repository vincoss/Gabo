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
	 5. avrdude -p atmega328p -c arduino -P COM4 -b 57600 -D -U flash:w:main.hex
 */ 

#include <string.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "GaboAdc.h"
#include "GaboIo.h"
#include "GaboUsart.h"
#include "GaboCommand.h"
#include "GaboSpi.h"
#include "GaboLoop.h"
#include "GaboTime.h"

int main(int argc, char *argv[])
{
	InitializeDefaults();
	GaboUsartInitialize();
	GaboUsartInterruptInitialize();
	GaboTimeIninialize();
	GaboSpiInitialize();
	GaboSpiIoInitialize();

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

		// Now clear data_in, the USART can reuse it now
		memset(srcData, 0, 8);
	}
}

void GaboCommandWriteLog(const char * message)
{
	if (message == NULL || strlen(message) <= 0)
	{
		return; // Nothing
	}
	
	GaboUsartWriteCharString(message);
	GaboUsartWriteChar('\r\n');
}

#pragma endregion GaboCommand implementation

#pragma region GaboLoop implementation

void GaboLoopMain(void)
{
	const int eventOneMilliseconds = 1;
	const int eventTwoMilliseconds = 1000 / 25; // Run every 50 millisecond.

	volatile unsigned long long int eventOneTicks = GaboTimeGetTickCount();
	volatile unsigned long long int eventTwoTicks = GaboTimeGetTickCount();

	while (1)
	{
		if((GaboTimeGetTickCount() - eventOneTicks) >= eventOneMilliseconds) // Every 1ms
		{
			GaboLoopOnUpdateMs();
			
			eventOneTicks = GaboTimeGetTickCount();
		}
		
		if((GaboTimeGetTickCount() - eventTwoTicks) >= eventTwoMilliseconds) // Every 50ms
		{
			GaboLoopOnUpdate();
			
			eventTwoTicks = GaboTimeGetTickCount();
		}
		
		GaboLoopOnRender();
	}
}

void GaboLoopOnUpdate(void)
{
	/*
		NOTE: Order is important.
		
		Highest priority
		
		*Read commands
		*Read sensors
		*Calculate
		*Push commands and calc values
	*/
	
	GaboCommandRead();
	
	// Do not execute if input commands are incoming or processing.
	if(startWriteCommand == 0)
	{
		ProcessOutputBus();
	}
	
	/*
		Lowest priority.
	*/
}

void GaboLoopOnUpdateMs(void)
{
	// TODO: check if can already read
	//ProcessInputBus();
}

void GaboLoopOnRender()
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
		
		GaboSpiSend(PowerCommand);
		GaboSpiSend(PowertrainCommand);
		// More commands here
		
		GABOIO_SPI_SET_OUTPUT_LATCH_HIGH;
		
		IsOutputInitialized = 1;
	}
}

void InitializeDefaults()
{
	IsOutputInitialized = 0;
}


// TODO: move int main.c

ISR(USART_RX_vect)
{
	char status, data;

	status = UCSR0A;
	data = UDR0;

	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) != 0)
	{
		return;
	};

	GaboCommandReadUsart(data);
}