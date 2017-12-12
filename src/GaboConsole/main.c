#include <stdio.h>
#include "GaboCommand.h"
#include "GaboIo.h"




void CommandLoopSample(void);

// A=255\nB=2\nA?\n
int main(void)
{
	GaboCommandPrint('A', 34);
	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}

void CommandLoopSample(void)
{
	int commandIndex = 0;

	while (1)
	{


		commandIndex++;
	}
}

