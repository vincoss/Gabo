//#pragma region Steps
//
//// Steps order is important
//
//// # System initialize
//// External power turn on/off (with button)
//// Initialize the system
//// Other taks later
//
//// # Drive
//// Power on/off
//
//// # Power Take Off
//// Power on/off
//
//#pragma endregion
//
//
//#ifndef F_CPU
//#define F_CPU 20000000UL	// or whatever may be your frequency
//#endif
//
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
//
//void InitializeDefaults();
//
//void Loop(void);
//void SetupTimer(void);
//void ReadSensor(void);
//void CalculateOutput(void);
//void OutputControl(void);
//
//void SensorBumper(void);
//void SensorUltrasound(void);
//
//uint8_t IsBitSet(uint8_t value, uint8_t bitindex);
//void SetBitAsUsed(uint8_t * value, uint8_t bitIndex);
//void SetBitAsUnUsed(uint8_t * value, uint8_t bitIndex);
//
//// on, off, brake, forward, reverse
//// 0/1	off/on
//// 0/1	brake off/brake on
//// 0/1	forward/reverse
//
//// 0 = init the system
//// 1 = cruise (0 = Brake, 1 = Run
//// 2 = navigation
//
//// 0 Drive Power	(0 off, 1 on)
//// 1 Power Take Off	(0 off, 1 on)
//volatile uint8_t _robotState;
//
//volatile uint8_t _driveSpeed; // 0-255
//volatile uint8_t _sensorState;
//
//
//#define DrivePowerPinD2			2
//#define PowerTakeOffPinD3		3
//
//#define SENSOR_BUMPER			0
//#define CRUISE_NAVIGATE			1
//#define CRUISE_BRAKE_PIN_INDEX	2
//
//#define LR_MOTOR_POWER_ON_OFF_PINB1		1
//#define L_MOTOR_START_STOP_PINB5		5
//#define R_MOTOR_START_STOP_PINB4		4
//#define LR_MOTOR_RUN_BRAKE_PIND7		7
//#define L_MOTOR_CW_CCW_PINB3			3
//#define L_MOTOR_CW_CCW_PINB2			2
//#define LR_Motor_Ground_PinD5			5
//
//
//volatile int _driveMotorNavigationCountTemp;
//
//volatile uint8_t _timerEvent;
//volatile uint8_t _timerEventRunning;
//
//void InitializeDefaults()
//{
//	_robotState = 0;
//	_driveSpeed = 0;
//	_sensorState = 0;
//	_timerEvent = 0;
//
//	// Drive power off (must set default to ensure relay is not turned on on power reset
//
//	PORTD |= (1 << DrivePowerPinD2);	// High relay off
//	PORTD |= (1 << PowerTakeOffPinD3);	// High relay off
//	DDRD |= (1 << DrivePowerPinD2);		// output
//	DDRD |= (1 << PowerTakeOffPinD3);	// output
//
//}
//
//void Loop(void)
//{
//	SetupTimer();
//	SystemInitialize();
//	InitializeDefaults();
//	DriveMotorInitialize(); // TODO: must not be here
//
//	while (1)
//	{
//		if (_timerEvent == 1)
//		{
//			_timerEvent = 0;
//
//			// NOTE: order these by importance. Highest
//			ReadSensor();
//			CalculateOutput();
//			OutputControl();
//			DriveMotorNavigation();
//			DriveMotorCruise();
//			// Lowest priority
//
//			_timerEventRunning = 0;
//		}
//	}
//}
//
//#pragma region Timer methods
//
//void SetupTimer(void)
//{
//	// TODO: review the timer logic, why timer1 not timer 2???
//	cli();		// Disable global interupts
//
//	TCCR1A = 0;     // set entire TCCR1A register to 0
//	TCCR1B = 0;     // same for TCCR1B
//
//	TCNT1 = 0;		// initialize counter
//	OCR1A = 0x30D3;	// Fire every 50ms, Run at 20Hz
//
//	_timerEvent = 0;
//
//	// Prescaler 64
//	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
//
//	// enable compare interrupt
//	TIMSK1 |= (1 << OCIE1A);
//
//	sei();	// enable global interrupts
//}
//
//// ISR is fired whenever a match occurs
//ISR(TIMER1_COMPA_vect)
//{
//	if (_timerEventRunning == 1)
//	{
//		return;
//	}
//
//	_timerEvent = 1;
//	_timerEventRunning = 1;
//}
//
//#pragma endregion
//
//#pragma region Sensor group methods
//
//void ReadSensor(void)
//{
//	SensorBumper();
//}
//
//void CalculateOutput(void)
//{
//
//}
//
//void OutputControl(void)
//{
//
//}
//
//#pragma endregion
//
//#pragma region Sensor implementation methods
//
//void SensorBumper(void)
//{
//	// TODO: move this into DriveMotorCruise
//	if (IsBitSet(_robotState, SENSOR_BUMPER) == 0)
//	{
//		return;
//	}
//
//	SetBitAsUsed(&_robotState, 0); // Brake ON
//}
//
//#pragma endregion
//
//#pragma region System methods
//
//void SystemInitialize(void);
//
//void SystemInitialize(void)
//{
//
//}
//
//#pragma endregion
//
//#pragma region Drive methods
//
//void DriveTurnOn(void);
//void DriveTurnOff(void);
//
//void DriveMotorInitialize(void);
//void DriveMotorNavigation(void);
//void DriveMotorCruise(void);
//
//// Ensure drive motor defauls
//void DriveMotorInitialize(void)
//{
//	if (IsBitSet(_robotState, 0) == 0) // off
//	{
//		// Order is important
//		PORTB |= ((1 << L_MOTOR_START_STOP_PINB5) | (1 << R_MOTOR_START_STOP_PINB4)); // Stop motor
//		PORTD |= (1 << DrivePowerPinD2);	// Turn power off
//		return;
//	}
//
//	// Motor driver power on/off
//	PORTD &= ~(1 << DrivePowerPinD2); // Low (On)
//
//	// Start/Stop
//	PORTB &= ~((1 << L_MOTOR_START_STOP_PINB5) & (1 << R_MOTOR_START_STOP_PINB4));
//	DDRB |= ((1 << L_MOTOR_START_STOP_PINB5) | (1 << R_MOTOR_START_STOP_PINB4));
//
//	// Run/Brake
//
//	PORTD |= (1 << LR_MOTOR_RUN_BRAKE_PIND7); // High to keep brake on
//	DDRD |= (1 << LR_MOTOR_RUN_BRAKE_PIND7);
//
//	// Cw/Ccw
//	PORTB &= ~((1 << L_MOTOR_CW_CCW_PINB3) & (1 << L_MOTOR_CW_CCW_PINB3));
//	DDRB |= ((1 << L_MOTOR_CW_CCW_PINB3) | (1 << L_MOTOR_CW_CCW_PINB3));
//
//	// Ground
//	PORTD |= (1 << LR_Motor_Ground_PinD5); // High
//	DDRD |= (1 << LR_Motor_Ground_PinD5);
//}
//
//void DriveMotorNavigation(void)
//{
//	// Left, right, default
//
//	// Default 0
//	// Left 1
//	// Right 2
//
//	_driveMotorNavigationCountTemp++;
//
//	if (_driveMotorNavigationCountTemp == 60)
//	{
//	    SetBitAsUnUsed(&_robotState, CRUISE_BRAKE_PIN_INDEX);
//	}
//
//	if (_driveMotorNavigationCountTemp == 120)
//	{
//		SetBitAsUsed(&_robotState, CRUISE_BRAKE_PIN_INDEX);
//		_driveMotorNavigationCountTemp = 0;
//	}
//}
//
//void DriveMotorCruise(void)
//{
//	// Brake On
//	if (IsBitSet(_robotState, CRUISE_BRAKE_PIN_INDEX) == 1) // High
//	{
//		PORTD |= (1 << LR_MOTOR_RUN_BRAKE_PIND7);
//		return;
//	}
//
//	// Brake Off
//	if (IsBitSet(_robotState, CRUISE_BRAKE_PIN_INDEX) == 0) // Low
//	{
//		PORTD &= ~(1 << LR_MOTOR_RUN_BRAKE_PIND7);
//		return;
//	}
//}
//
//#pragma endregion
//
//#pragma region Utility methods
//
//uint8_t IsBitSet(uint8_t value, uint8_t bitindex)
//{
//	return ((value & (1 << bitindex)) != 0) ? 1 : 0;
//}
//
//void SetBitAsUsed(uint8_t * value, uint8_t bitIndex)
//{
//	 *value = (*value | 1 << bitIndex);
//}
//
//void SetBitAsUnUsed(uint8_t * value, uint8_t bitIndex)
//{
//	 *value = (*value & ~(1 << bitIndex));
//}
//#pragma endregion
//
//
///////////////////////////////////////////////////////////////////////////// Temp
//
////#pragma region TEMP
////
////int DriveMotorVrh;
////int DriveMotorVrm;
////int DriveMotorVrl;
////int DriveMotorSpeed;
////int DriveMotorAlarm;
////
//////struct Command
//////{
//////	uint8_t Cmd; // speed
//////	uint8_t Arg; // steering
//////	uint8_t State; // bit
//////};
//////
//////struct Command _commands[5] = { _navigation };
////
////
////
////// Ultrasound sensors should cover 90 degree view from the front
////
////
////void SampleTwo(void)
////{
////	DDRB |= (1 << PB5);
////	DDRB |= (1 << PB4);
////	DDRB |= (1 << PB3);
////	DDRB |= (1 << PB2);
////	DDRB |= (1 << PB1);
////	DDRB |= (1 << PB0);
////
////	PORTB |= (1 << PB5);
////	PORTB |= (1 << PB4);
////	PORTB |= (1 << PB3);
////	PORTB |= (1 << PB2);
////	PORTB &= ~(1 << PB1);
////	PORTB |= (1 << PB0);
////
////	while (1)
////	{
////
////	}
////}
////
////#define RightStartStop = 5;
////#define RunBrake = 4; // used by both wheels
////#define RightCwCcw = 3;
////
//////unit8_t leftMotor = 0; 
////
//////00000000;
////// 00000001 start/stop
////// 00000010 run/brake
////// 00000100 cw/ccw
////// 00001000 
////
////
////// start (moving)
////// stop (gradual stop)
////// run (moving)
////// brake (immediate stop)
////// CW (move forward)
////// CCW (move backward)
////
////char DriveMotorStartStop;
////char DriveMotorRunBrake;
////char DriveMotorCwCcw;
////char DriveMotorIntVrExt;
////char DriveMotorAlarmReset;
////int DriveMotorVrh;
////int DriveMotorVrm;
////int DriveMotorVrl;
////int DriveMotorSpeed;
////
////#define BUMP 1
////#define MOTION 2
////#define IR 4
////#define BOUNDARY 8
////#define SONAR 0x10
////#define PHOTO 0x20
////#define XLATE 0x40
////#define PROWL 0x80
////#define DEFAULT 0x100 
////
////
////
////
////#define START (1 << 0);
////#define NAVIGATION_ACTIVE = (1 << 2);
////
////// Loop
////// Started?
////// Cruise tasks
////// Cruise clear?
////// Cruise
////
////// Steps
////// 1. check bumper
////// 2. forwad
////// 3. bumper activated
////// 4. reverse
////// 5. bumper activated
////// 6. forward
////
////// High OFF
////// Low	ON
////
////// loop 
////// set all low
////
////// loop
////// bumper
////// set brake on
////
////
////#pragma endregion
////
////#pragma region Logging & telemetry
////
////// should alow to enable loggin and telemetry, always check if enabled 
////
////#pragma endregion
//
///*
//
//LEFT (Output) where high working
//0	Left - start/stop
//1	Left - run/brake
//2	Left - cw/cw
//3	Right - start/stop
//4	Right - run/brake
//5	Right - cw/cw
//6	Left|Right - in/out pot (NOTE: this connect just to 5V since always internal
//7	Left|Right - alert-on/off
//
//??
//
//0x00000000
//0x00011111
//
//Left(input)
//Speed-/Up/Down (0-100%)
//
//Need two shift registers or one 16 bit one.
//
//*/
//
///*
//
//	NOTE: we need two commands for powertrain
//		Left
//		Right
//
//	1. Start powertrain loop
//	2. read command (if local command is null then command was never send to powertrain registers)
//	3. check command agains local command and if changed then send to the registers
//
//	// Create register header file for SPI and other
//	then add that into powerthrain header
//
//	# header files
//	GaboIo.h
//	GaboSpi.h
//
//	projects
//	Gabo
//	Gabo.Tests
//
//	c code share values between header files
//
//
//	https://cs50.stackexchange.com/questions/1111/how-do-i-share-a-variable-between-source-files-in-c-with-extern
//	https://circuitnegma.wordpress.com/2008/07/16/c-programming-how-to-use-a-variable-in-multipledifferent-source-files/
//	https://stackoverflow.com/questions/1045501/how-do-i-share-variables-between-different-c-files
//	https://stackoverflow.com/questions/11193098/sharing-variables-structures-at-header-files-all-over-the-program
//
//	Example
//
//	Main
//		variable powertrainCommand
//
//		main loop
//
//		ReadCommand()
//
//		Powertrain(powertrainCommand);
//		PowerOff(command)
//		Sensor(command)
//
//		#Speed
//		L	0-100 %
//		R	0-100 %
//		00000000 TODO: need to store two values 0 to 100 for left and right
//
//		#Command groups
//		powertrain			0
//		powertrain speed	1
//
//		#Command example, use all characters A-Z upper case
//		A={command}
//		? for query
//		: for response
//		= to set 
//		Then read into a variable until /n
//
//		#Example
//		A=SomeCommand\n (usart reads two bytes
//
//		POWERTRAIN 8 bits
//		L START/STOP
//		L RUN/BRAKE
//		L CW/CCW
//		R
//		R
//		R
//		LR ALERT ON/OFF
//		?
//
//*/
//
//#define PowertrainCommand		0
//#define PowertrainSpeedCommand	1
//
//int main2()
//{
//	uint8_t powertrainCommand;
//	uint8_t powertrainCommandPrevious;
//	uint8_t powertrainSpeedCommand;
//
//	powertrainCommand = -1;
//	powertrainSpeedCommand = -1;
//
//	while (1)
//	{
//		uint8_t command = ReadInputCommand(PowertrainCommand);
//
//		Powertrain(powertrainCommandPrevious, powertrainCommand);
//
//		if(powertrainCommand == -1 || powertrainCommand != command)
//		{
//			PowertrainPut(powertrainCommand);
//		}
//
//		command = ReadInputCommand(PowertrainSpeedCommand);
//
//		// TODO: need to check whether powertrain is actually running
//		if (powertrainCommand != -1 && (powertrainSpeedCommand == -1 || powertrainSpeedCommand != command))
//		{
//			PowertrainPutSpeed(powertrainCommand);
//		}
//	}
//	return 0;
//}
//
//void Powertrain(uint8_t previousCommand, uint8_t command)
//{
//	if (previousCommand == command)
//	{
//		return;
//	}
//
//	PowertrainPut(command);
//}
//
//uint8_t ReadInputCommand(uint8_t commandGroup)
//{
//	switch (commandGroup)
//	{
//		case 0:	// Powertrain
//		{
//			// 7F
//			return 0b01111111; // for now just powertrain functionality
//		}
//		case 1: // Powertrain speed
//		{
//			return 0b0;
//		}
//		default:
//			return 0;
//	}
//}
//
//void PowertrainPut(uint8_t command)
//{
//	SpiTransfer(command);
//}
//
//void PowertrainPutSpeed(uint8_t command)
//{
//
//}
//
//void SpiInitialize(void)
//{
//
//}
//
//uint8_t SpiTransfer(uint8_t data)
//{
//	return -1;
//}
//
//uint8_t PowertrainIsStarted(uint8_t command)
//{
//	// off	0, on	1 just check the command bits wheter power train is on
//	return 1;
//}
