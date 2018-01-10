//	Copy main.hex into Arduino board use this command
//	1. Open command prompt
//	2. cd {SolutionDir}
//	3. avrdude -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:main.hex


#include <avr\io.h>
#include <util\delay.h>

//#include "GaboUsart.h"
//#include "GaboCommand.h"

int main(int argc, char *argv[])
{
	/*GaboUsartInitialize();

	while (1)
	{
		GaboCommandProcess();
	}*/

	return 0;
}