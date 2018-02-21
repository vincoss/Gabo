/*
 * GaboTime.h
 *
 * Created: 20/02/2018 5:25:59 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABOTIME_H_
#define GABOTIME_H_

volatile unsigned long long GaboTimeTickCount;

void GaboTimeIninialize(void);
unsigned long long GaboTimeGetTickCount(void);

unsigned long long GaboTimeGetTickCount(void)
{
	return 0;
}

#endif /* GABOTIME_H_ */