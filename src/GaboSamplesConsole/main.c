#include <stdio.h>
#include "CommandSample.h"


void PrintInputCommands(int argc, char *argv[]);
void CommandSamples();


int main(int argc, char *argv[])
{
	CommandSamples();
	//PrintInputCommands(argc, argv);

	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}

void PrintInputCommands(int argc, char *argv[])
{
	int i;

	printf("The following arguments were passed to main(): ");
	for (i = 1; i < argc; i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
}

void CommandSamples()
{
	CommandSample_Main();
}