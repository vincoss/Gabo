
// TODO: add loggin/telemery or trace


/*

	TODO: See Mcp4xxx.c implementation, for command and error repsponse bits.

	# In Commands

	Power ON/OFF	0
	Start/Stop		1
	Run/Brake		2
	Cw/Ccw			3
	Speed			4 + data (0-100)
	Direction		5 + data (0-360)
	AlarmReset		6

	# Groups
	
	Powertrain		0
	PowertakeOff	1

	// 32 bits (control for powertrain)
	{group}{direction}{speed}{command}
	{direction}{speed}{command}{group}
	{9}{7}{8}{8}

	// Sample powertrain power off/on
	0-00000000
	0-00000001

	NOTE: should be possible to set power on, start, run, cw, speed, directon, alert with one command

	Example
	Command 00111111
	Data	

	
	# Out Commands // Need to think about this
	
	Read Left	0
	Read Right	1


	#Obsolete
	Power OFF	0
	Power ON	1
	Start		2
	Stop		3
	Run			4
	Brake		5
	Cw			6
	Ccw			7
	Speed		8	TODO: needs actual speed value in percent
	Direction	9	TODO: needs degrees value to turn to 0-360
	Clear Alert LR 10
	
	0,1,2,4,8,16,32,64,128
*/


// 8 Bits (TODO: looks that speed needs 16 bits or pass individual command
// add activateCommand (last command when all comand were already input in)
// Left		0-100
// Right	0-100
//  128 64 32 16 8421			
//	0    0  0  0 0000