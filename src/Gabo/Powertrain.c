#include "Utility.h"
#include "Powertrain.h"
#include "Adc.h"
#include "Mcp4xxx.h"
#include <stdlib.h>


#pragma region Public methods


void PowertrainSpiSetup(void)
{
	DDRB = (1 << 2) | (1 << 3) | (1 << 5);
	Mcp4xxxInitialize(&PORTB, 2);
}

void PowertrainSetup(void)
{
	PowertrainSpiSetup();

	DDRD |= (1 << POWERTRAIN_POWER_ON_OFF_PIND2);		// Output
	DDRD |= ((1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5) | (1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5));		// Output
	DDRD |= (1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3);
	DDRD |= ((1 << POWERTRAIN_L_MOTOR_CW_CCW_PINB2) | (1 << POWERTRAIN_R_MOTOR_CW_CCW_PINB1));

	// TODO: Ground this is issue if power is not not???

	// Ground
	PORTD |= (1 << POWERTRAIN_LR_MOTOR_GROUND_PINB0); // High
	DDRD |= (1 << POWERTRAIN_LR_MOTOR_GROUND_PINB0);

	// Speed // TODO: temp remove
	/*DDRA &= ~(1 << POWERTRAIN_L_MOTOR_SPEED_PINA0);
	DDRA &= ~(1 << POWERTRAIN_R_MOTOR_SPEED_PINA1);*/
}

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

void PowertrainRun(void)
{
	UtilitySetBitAsUsed(&_powertrainState, PowertrainStateRunBrakeBit2);
}

void PowertrainBrake(void)
{
	UtilitySetBitAsUnUsed(&_powertrainState, PowertrainStateRunBrakeBit2);
}

void PowertrainCw(void)
{
	UtilitySetBitAsUsed(&_powertrainState, PowertrainStateCwCcwBit3);
}

void PowertrainCcw(void)
{
	UtilitySetBitAsUnUsed(&_powertrainState, PowertrainStateCwCcwBit3);
}

void PowertrainLoop(void)
{
	// NOTE: order is important

	// Power on/off
	if (UtilityIsBitSet(_powertrainState, PowertrainStateOnOffBit0) == UTILITY_ON)
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
	if (UtilityIsBitSet(_powertrainState, PowertrainStateRunBrakeBit2) == UTILITY_ON)
	{
		InternalPowertrainRun();
	}
	else
	{
		InternalPowertrainBrake();
	}

	// Motor start/stop
	if (UtilityIsBitSet(_powertrainState, PowertrainStateStartStopBit1) == UTILITY_ON)
	{
		InternalPowertrainStart();
	}
	else
	{
		InternalPowertrainStop();
	}

	// Motor Cw/Ccw
	if (UtilityIsBitSet(_powertrainState, PowertrainStateCwCcwBit3) == UTILITY_ON)
	{
		InternalCw();
	}
	else
	{
		InternalCcw();
	}

	InternalSpeed();
}

#pragma endregion

#pragma region Internal methods

void InternalPowertrainOn(void)
{
	// Power on
	PORTD &= ~(1 << POWERTRAIN_POWER_ON_OFF_PIND2);		// Low - turn powertrain power on
}

void InternalPowertrainOff(void)
{
	// NOTE: Order is important
	PORTD |= (1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3);	// High - brake on
	PORTD |= (1 << POWERTRAIN_POWER_ON_OFF_PIND2);			// High - turn powertrain power off
}

void InternalPowertrainStart(void)
{
	PORTD &= ~((1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5) & (1 << POWERTRAIN_R_MOTOR_START_STOP_PINB4));	// Low - start
}

void InternalPowertrainStop(void)
{
	PORTD |= ((1 << POWERTRAIN_L_MOTOR_START_STOP_PINB5) | (1 << POWERTRAIN_R_MOTOR_START_STOP_PINB4));		// High - stop
}

void InternalPowertrainRun(void)
{
	PORTD &= ~(1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3); // Low - brake off
}

void InternalPowertrainBrake(void)
{
	PORTD |= (1 << POWERTRAIN_LR_MOTOR_RUN_BRAKE_PINB3); // High - brake on
}

void InternalCw(void)
{
	PORTD &= ~((1 << POWERTRAIN_L_MOTOR_CW_CCW_PINB2) & (1 << POWERTRAIN_R_MOTOR_CW_CCW_PINB1)); // TODO: comment find what direction is this
}

void InternalCcw(void)
{
	PORTD |= ((1 << POWERTRAIN_L_MOTOR_CW_CCW_PINB2) | (1 << POWERTRAIN_R_MOTOR_CW_CCW_PINB1)); // TODO: comment find what direction is this
}

void PowertrainSpeed(uint8_t percent)
{
	// TODO: must reverse this since higher percent more resistance LOL
	Mcp4xxxSetBothWiperByPercent(percent);
}

// TODO: temp only
char adcSamplesThree_Buffer[5];

void InternalSpeed(void)
{
	uint16_t value = AdcRead(5);

	itoa(value, adcSamplesThree_Buffer, 10);
	UsartWriteCharString(adcSamplesThree_Buffer);
	
	UsartWriteChar('\n');
}

#pragma endregion

// TODO:
// R4 zajiš?uje, že b?hem programování mikrokontrolér nep?ijímá potenciometr data. 
// When programming writing into chip must not reset the relay and other

