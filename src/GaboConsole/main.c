#include <stdio.h>

int main()
{
	UnitTestsRun();

	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}

void GaboCommandCopy(char * srcData, char * destCommand)
{
	if (strlen(srcData) <= 0)
	{
		return;
	}

	// Copy the contents of data_in into command_in
	memcpy(destCommand, srcData, 8);

	//// Now clear data_in, the USART can reuse it now
	memset(srcData, 0, 8);
}

