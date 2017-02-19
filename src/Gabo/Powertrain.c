#include "Utility.h"
#include "Powertrain.h"


#pragma region Public methods

void PowertrainTurnPowerOn(void)
{
	UtilitySetBitAsUsed(&_powertrainState, PowertrainStateOnOffBit0);
}

void PowertrainTurnPowerOff(void)
{
	UtilitySetBitAsUnUsed(&_powertrainState, PowertrainStateOnOffBit0);
}

void PowertrainStart(void)
{
	UtilitySetBitAsUsed(&_powertrainState, PowertrainStateStartStopBit1);
}

void PowertrainStop(void)
{
	UtilitySetBitAsUnUsed(&_powertrainState, PowertrainStateStartStopBit1);
}

void PowertrainBrake(void)
{
	UtilitySetBitAsUsed(&_powertrainState, PowertrainStateRunBrakeBit2);
}

void PowertrainRun(void)
{
	UtilitySetBitAsUnUsed(&_powertrainState, PowertrainStateRunBrakeBit2);
}

void PowertrainLoop(void)
{
	// NOTE: order is important

	// Power on/off
	if (UtilityIsBitSet(_powertrainState, PowertrainStateOnOffBit0) == ON)
	{
		InternalPowertrainOn();
	}
	else
	{
		InternalPowertrainOff();

		// Just return no need to execute other actions
		return;
	}

	// Motor run/brake
	if (UtilityIsBitSet(_powertrainState, PowertrainStateRunBrakeBit2) == ON)
	{
		InternalPowertrainRun();
	}
	else
	{
		InternalPowertrainBrake();
	}

	// Motor start/stop
	if (UtilityIsBitSet(_powertrainState, PowertrainStateStartStopBit1) == ON)
	{
		InternalPowertrainStart();
	}
	else
	{
		InternalPowertrainStop();
	}

	// Motor Cw/Ccw
	if (UtilityIsBitSet(_powertrainState, PowertrainStateCwCcwBit3) == ON)
	{
		InternalCw();
	}
	else
	{
		InternalCcw();
	}
}

#pragma endregion

void InternalPowertrainOn(void)
{
	// Power on
	PORTD &= ~(1 << POWERTRAIN_POWER_ON_OFF_PIND2);		// Low - turn powertrain power on
}

void InternalPowertrainOff(void)
{
	// NOTE: Order is important
	PORTB |= (1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3);	// High - brake on
	PORTD |= (1 << POWERTRAIN_POWER_ON_OFF_PIND2);			// High - turn powertrain power off
}

void InternalPowertrainStart(void)
{
	PORTB &= ~((1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5) & (1 << POWERTRAIN_R_MOTOR_START_STOP_PINB4));	// Low - start
}

void InternalPowertrainStop(void)
{
	PORTB |= ((1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5) | (1 << POWERTRAIN_R_MOTOR_START_STOP_PINB4));		// High - stop
}

void InternalPowertrainRun(void)
{
	PORTB &= ~(1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3); // Low - brake off
}

void InternalPowertrainBrake(void)
{
	PORTB |= (1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3); // High - brake on
}

void InternalCw(void)
{
	PORTB &= ~((1 << POWERTRAIN_L_MOTOR_CW_CCW_PINB2) & (1 << POWERTRAIN_R_MOTOR_CW_CCW_PINB1)); // TODO: comment find what direction is this
}

void InternalCcw(void)
{
	PORTB |= ((1 << POWERTRAIN_L_MOTOR_CW_CCW_PINB2) | (1 << POWERTRAIN_R_MOTOR_CW_CCW_PINB1)); // TODO: comment find what direction is this
}


void PowertrainSetup(void)
{

	// TODO: this is issue if power is not not???

	// Ground
	PORTD |= (1 << POWERTRAIN_LR_MOTOR_GROUND_PINB0); // High
	DDRD |= (1 << POWERTRAIN_LR_MOTOR_GROUND_PINB0);


	DDRD |= (1 << POWERTRAIN_POWER_ON_OFF_PIND2);		// Output
	DDRB |= ((1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5) | (1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5));		// Output
	DDRB |= (1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3);
	DDRB |= ((1 << POWERTRAIN_L_MOTOR_CW_CCW_PINB2) | (1 << POWERTRAIN_R_MOTOR_CW_CCW_PINB1));
}