// CATAPULT VARIABLES
int cocksBack;
int shootFwd;
int openClaw;
int closeClaw;
int shootWheel;
int pistonOut;
int pistonIn;

int calibrate;
int fold;

	//Driver Profiles
	//Change names for drivers
	int driver_1;
	int driver_2;
	int driver_3;
	string first;
	string second;
	string third;

//Manipulator Functions

/*------------------------------------------------------------------------------------------------------*/

//Function for Driver Profiles.
void driverSelect(string driver)
{
	//Change String names for the different user names.


	if(driver == first)
	{
		driver_1 = 1;
		driver_2 = 0;
		driver_3 = 0;
	}
	if(driver == second)
	{
		driver_1 = 0;
		driver_2 = 1;
		driver_3 = 0;
	}
	if(driver == third)
	{
		driver_1 = 0;
		driver_2 = 0;
		driver_3 = 1;
	}
}

//Setting the Manipulator variables in relation to the profiles.
//Change the port locations to customize each profile to the driver's preference.
void manipVariables()
{
	if(driver_1)
	{
		shootFwd = vexRT[Btn5D];
		cocksBack = vexRT[Btn5U];
		openClaw = vexRT[Btn6D];
		closeClaw = vexRT[Btn6U];
		calibrate = vexRT[Btn8R];
		shootWheel = vexRT[Btn8U];
		pistonOut = vexRT[Btn7L];
		pistonIn = vexRT[Btn7R];
	}
	if(driver_2)
	{
		shootFwd = vexRT[Btn5U];
		cocksBack = vexRT[Btn5D];
		openClaw = vexRT[Btn6U];
		closeClaw = vexRT[Btn6D];
		calibrate = vexRT[Btn8R];
		shootWheel = vexRT[Btn8U];
		pistonOut = vexRT[Btn7L];
		pistonIn = vexRT[Btn7R];
	}
	if(driver_3)
	{
		shootFwd = vexRT[Btn6U];
		cocksBack = vexRT[Btn6D];
		openClaw = vexRT[Btn5U];
		closeClaw = vexRT[Btn5D];
		calibrate = vexRT[Btn8R];
		shootWheel = vexRT[Btn8U];
		pistonOut = vexRT[Btn7L];
		pistonIn = vexRT[Btn7R];
	}
}

/*----------------------------------------------------------------------------------------------------*/

//Claw functions
//Designed for a 2 motor claw. Modify if necessary

//initilization for the claw.
void claw(int speed)
{
	motor[left_claw_motor] = speed;
	motor[right_claw_motor] = speed;
}

void moveClaw()
{
	if(openClaw)
	{
		claw(127);
	}
	else if(closeClaw)
	{
		claw(-127);
	}
	else
	{
		claw(0);
	}
}

//A claw motion to be used for autonomous or other locations
void open_Claw(int time)
{
	claw(127);
	wait1Msec(time);
	claw(0);
}
void close_Claw(int time)
{
	claw(-127);
	wait1Msec(time);
	claw(0);
}

/*----------------------------------------------------------------------------------------------------*/

//Flywheel (shooter) Functions
//Designed for a 2 motor flywheel or a 2 motor intake roller system. Modify if necessary

//initilizes the flywheel
void flywheel(int speed)
{
	motor[left_fly_motor] = speed;
	motor[right_fly_motor] = speed;
}

//starts the shooting motor.
void startFlyWheel()
{
	if(shootWheel == 1)
	{
		flywheel(127);
	}
	else
	{
		flywheel(0);
	}
}

/*-------------------------------------------------------------------------------------------------*/

//Pneumatic Functions
//Designed for one piston. Modify if necessary

//initilization of piston
void piston(int state)
{
	SensorValue[solenoid] = state;
}

//Piston control
void movePiston()
{
	if(pistonOut == 1)
	{
		piston(1);
	}
	else if(pistonIn == 1)
	{
		piston(0);
	}
}

/*------------------------------------------------------------------------------------------------*/

//Arm Functions
//Designed for a four motor arm lift. Modify if necessary.

//Left side set
void updateLeftArmMotors(int Speed)
{
	motor[bot_left_cat] = -Speed;
	motor[top_left_cat] = Speed;
}

//Right side set
void updateRightArmMotors(int Speed)
{
	motor[top_right_cat] = Speed;
	motor[bot_right_cat] = -Speed;
}

//Both sides set
//This can be used as a shortcut for something like autonomous or other functions.
void updateArmMotors(int Speed)
{
	updateRightArmMotors(Speed);
	updateLeftArmMotors(Speed);
}

//This is an action which calibrates an encoder to the lowered arm position.
void calibrateArm()
{
	if(calibrate)
	{
		updateArmMotors(-50);
		wait1Msec(2000);
		updateArmMotors(0);
		SensorValue[ArmEncoder] = 0;
	}
}

//Function for the arm movement in Teleoperated
void armMoveTeleop()
{
	if(cocksBack == 1)
	{
		updateArmMotors(-100); //goin dwn
	}
	else if(shootFwd == 1)
	{
		updateArmMotors(127);
	}
	else
	{
		updateArmMotors(0);
	}
}

/*----------------------------------------------------------------------------------------------------*/
