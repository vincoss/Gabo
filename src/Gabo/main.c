//	Copy main.hex into Arduino board use this command
//	1. Open command prompt
//	2. cd {SolutionDir}
//	3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex
//	4. Upload .hex & .eep file

#include <avr/interrupt.h>
#include <util/delay.h>		
#include "Usart.h"
#include "Utility.h"
#include "Powertrain.h"
#include "PowerTakeOff.h"
#include "Mcp4xxx.h"
#include "GaboIo.h"

int main(void)
{
	uint8_t powertrainCommand;
	uint8_t powertrainCommandPrevious;
	uint8_t powertrainSpeedCommand;

	powertrainCommand = -1;
	powertrainSpeedCommand = -1;

	while (1)
	{
		uint8_t command = ReadInputCommand(PowertrainCommand);

		Powertrain(powertrainCommandPrevious, powertrainCommand);

		if (powertrainCommand == -1 || powertrainCommand != command)
		{
			PowertrainPut(powertrainCommand);
		}

		command = ReadInputCommand(PowertrainSpeedCommand);

		// TODO: need to check whether powertrain is actually running
		if (powertrainCommand != -1 && (powertrainSpeedCommand == -1 || powertrainSpeedCommand != command))
		{
			PowertrainPutSpeed(powertrainCommand);
		}

		_delay_ms(500); // TODO: Use timer with interrupt, instead of this
	}
	return 0;
}

void Powertrain(uint8_t previousCommand, uint8_t command)
{
	if (previousCommand == command)
	{
		return;
	}

	PowertrainPut(command);
}

uint8_t ReadInputCommand(uint8_t commandGroup)
{
	switch (commandGroup)
	{
	case 0:	// Powertrain
	{
		// 7F
		return 0b01111111; // for now just powertrain functionality
	}
	case 1: // Powertrain speed
	{
		return 0b0;
	}
	default:
		return 0;
	}
}

void PowertrainPut(uint8_t command)
{
	SpiTransfer(command);
}

void PowertrainPutSpeed(uint8_t command)
{

}

void SpiInitialize(void)
{

}

uint8_t SpiTransfer(uint8_t data)
{
	return -1;
}

uint8_t PowertrainIsStarted(uint8_t command)
{
	// off	0, on	1 just check the command bits wheter power train is on
	return 1;
}


#pragma region Obsolete TODO: delete when not required
//
//int main(void)
//{
//	PowertrainSetup();
//	//PowertrainTurnPowerOn();
//	PowertrainStart();
//	PowertrainRun();
//	PowertrainCw();
//
//	PowertrainSpeed(50);
//
//	AdcInitialize();
//	UsartInitialize();
//	SetupIcmTimer();
//
//	DDRD &= ~(1 << PD6);
//	PORTD |= (1 << PD6);
//
//	while (1)
//	{
//		PowertrainLoop();
//		_delay_ms(500);
//	}
//
//	return 0;
//}
//
#pragma endregion


