//	Copy main.hex into Arduino board use this command
//	1. Open command prompt
//	2. cd {SolutionDir}
//	3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex
//	4. Upload .hex & .eep file

#include "Usart.h"
#include "Powertrain.h"
#include "PowerTakeOff.h"

int main(void)
{
	return 0;
}