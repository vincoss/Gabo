/*
 * GaboTime.h
 *
 * Created: 20/02/2018 5:25:59 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABOTIME_H_
#define GABOTIME_H_

void GaboTimeIninialize();

volatile unsigned long long GaboTimeTickCount;

unsigned long long GetTickCount(void)
{
	return GaboTimeTickCount;
}


#endif /* GABOTIME_H_ */