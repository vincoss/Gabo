/*
 * GaboPowertrain.h
 *
 * Created: 18/04/2018 8:04:08 AM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABOPOWERTRAIN_H_
#define GABOPOWERTRAIN_H_


void PowertrainStop();
void PowertrainLeftStop();
void PowertrainRightStop();
void PowertrainStart();
void PowertrainLeftStart();
void PowertrainRightStart();

void PowertrainRun();
void PowertrainBrake();
void PowertrainLeftRun();
void PowertrainRightRun();
void PowertrainLeftBrake();
void PowertrainRightBrake();

void PowertrainCw();
void PowertrainCcw();
void PowertrainLeftCw();
void PowertrainRightCw();
void PowertrainLeftCcw();
void PowertrainRightCcw();

void PowertrainClearAlarm();


#endif /* GABOPOWERTRAIN_H_ */