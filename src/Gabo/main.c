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

	while (1)
	{
		PowertrainLoop();

		_delay_ms(1000);
	}

	return 0;
}