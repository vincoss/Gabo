#include <avr/io.h>

volatile uint8_t _powertrainState;

#define PowertrainStateOnOffBit0		0	// On/Off power
#define PowertrainStateStartStopBit1	1	// Start/Stop
#define PowertrainStateRunBrakeBit2		2	// Run/Brake
#define PowertrainStateCwCcwBit3		3	// Cw/Ccw

// PORTD
#define POWERTRAIN_L_MOTOR_START_STOP_PINB5		7	//5
#define POWERTRAIN_R_MOTOR_START_STOP_PINB4		-1//6	//4
#define POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3		5	//3
#define POWERTRAIN_L_MOTOR_CW_CCW_PINB2			4	//2
#define POWERTRAIN_POWER_ON_OFF_PIND2			3	//1	POWERTRAIN_R_MOTOR_CW_CCW_PINB1
#define POWERTRAIN_LR_MOTOR_GROUND_PINB0		2	//0	
#define POWERTRAIN_R_MOTOR_CW_CCW_PINB1			1	//2	POWERTRAIN_POWER_ON_OFF_PIND2

// PORTB
#define POWERTRAIN_L_MOTOR_SPEED_PINA0	5
#define POWERTRAIN_R_MOTOR_SPEED_PINA1	1

void PowertrainSetup(void);

void PowertrainLoop(void);

void PowertrainTurnPowerOn(void);
void PowertrainTurnPowerOff(void);

void PowertrainStart(void);
void PowertrainStop(void);

void PowertrainBrake(void);
void PowertrainRun(void);

void InternalCw(void);
void InternalCcw(void);

void PowertrainSpeed(uint8_t percent);
