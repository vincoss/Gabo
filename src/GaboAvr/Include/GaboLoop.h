/*
 * GaboLoop.h
 *
 * Created: 15/03/2018 7:28:20 AM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABOLOOP_H_
#define GABOLOOP_H_

volatile uint8_t _mainLoopOnUpdateRunning;

void GaboLoopMain(void);

void GaboLoopOnUpdate(void);
void GaboLoopOnUpdateMs(void);
void GaboLoopOnRender(void);

#endif /* GABOLOOP_H_ */