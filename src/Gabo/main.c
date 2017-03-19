//	Copy main.hex into Arduino board use this command
//	1. Open command prompt
//	2. cd {SolutionDir}
//	3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex
//	4. Upload .hex & .eep file

#include "Usart.h"
#include "Utility.h"
#include "Powertrain.h"
#include "PowerTakeOff.h"
#include <util/delay.h>		
#include "Mcp4xxx.h"
#include <avr/interrupt.h>



int main(void)
{
	PowertrainSetup();
	//PowertrainTurnPowerOn();
	PowertrainStart();
	PowertrainRun();
	PowertrainCw();

	PowertrainSpeed(50);

	AdcInitialize();
	UsartInitialize();
	SetupIcmTimer();

	DDRD &= ~(1 << PD6);
	PORTD |= (1 << PD6);

	volatile long _speedCounter;
	char binary[9];

	while (1)
	{
		PowertrainLoop();
		_delay_ms(500);
	}

	return 0;
}

//// TODO: temp only
//char adcSamplesThree_Buffer[5];
//
//void InternalSpeed(void)
//{
//	uint16_t value = AdcRead(5);
//
//	itoa(value, adcSamplesThree_Buffer, 10);
//	UsartWriteCharString(adcSamplesThree_Buffer);
//
//	UsartWriteChar('\n');
//}
//
//#pragma endregion

// TODO:
// R4 zajiš?uje, že b?hem programování mikrokontrolér nep?ijímá potenciometr data. 
// When programming writing into chip must not reset the relay and other

/*
	# In Commands

	Power ON/OFF	0
	Start/Stop		1
	Run/Brake		2
	Cw/Ccw			3
	Speed			4 + data (0-100)
	Direction		5 + data (0-360)
	AlarmReset		6

	Power OFF	0
	Power ON	1
	Start		2
	Stop		3
	Run			4
	Brake		5
	Cw			6
	Ccw			7
	Speed		8	TODO: needs actual speed value in percent
	Direction	9	TODO: needs degrees value to turn to 0-360
	Clear Alert LR 10

	# Out Commands
	
	Read Left	0
	Read Right	1

	# Groups
	
	Powertrain		0
	PowertakeOff	1

	// 32 bits
	{group}{direction}{speed}{command}
	{8}{9}{7}{8}

	// Sample powertrain power off/on
	0-00000000
	0-00000001

	NOTE: should be possible to set power on, start, run, cw, speed, directon, alert with one command

	Example
	Command 00111111
	Data	
*/