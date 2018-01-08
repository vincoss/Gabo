#include "GaboUsart.h"
#include "GaboCommand.h"

int main(int argc, char *argv[])
{
	GaboUsartInitialize();

	while (1)
	{
		GaboCommandProcess();
	}

	return 0;
}