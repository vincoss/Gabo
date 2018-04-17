/*
 * GaboPowertrain.c
 *
 * Created: 18/04/2018 8:04:45 AM
 *  Author: Ferdinand Lukasak
 */ 

#include "GaboIo.h"
#include "GaboPowertrain.h"


void PowertrainStop()
{
	PowertrainLeftStop();
	PowertrainRightStop();
}

void PowertrainLeftStop()
{
	UtilitySetBitAsUnUsed(&PowertrainCommand, PINB0);
}

void PowertrainRightStop()
{
	UtilitySetBitAsUnUsed(&PowertrainCommand, PINB1);
}