
#include<stdio.h>
#include<string.h>
#include <inttypes.h>
#include "GaboCommand.h"
#include "GaboIo.h"
#include "UnitTests.h"


#ifndef _WIN32
#define _WIN32
#endif


int main()
{
	UnitTestsRun();

	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}


//void CommandLoopSample(void);
//void PrintInputCommands(int argc, char *argv[]);

/*
		//char tempcommand[64] = "A=255\nB=2\nA?\n";

	argv = "A=255\nB=2\nA?\n";
		argc = strlen(argv);
	
	//PrintInputCommands(argc, argv);
	//CommandLoopSample(argc, tempcommand);

*/

//void PrintInputCommands(int argc, char *argv[])
//{
//	int i;
//
//	printf("The following arguments were passed to main(): ");
//	for (i = 1; i < argc; i++)
//	{
//		printf("%s ", argv[i]);
//	}
//	printf("\n");
//}
//
//void CommandLoopSample(int argc, char * argv)
//{
//	int commandIndex = 0;
//
//	while (1)
//	{
//		char ch = argv[commandIndex];
//
//		GaboCommandReadUsart(ch);
//
//
//		if (command_ready == 1)
//		{
//			GaboCommandCopy(data_in, command_in);
//			GaboCommandProcess(command_in);
//			//process_command();
//
//			command_ready = 0;
//			//usart_ok();
//		}
//
//
//		printf("\n%s", command_in);
//		printf("\n%d", powerCommand);
//		printf("\n%d", commandPowertrain);
//
//		commandIndex++;
//	}
//}

