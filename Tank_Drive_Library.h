#include "PID.h"

int forward;
int turn;
int newStrafe;


int driveY;
int driveX;
int strafe;

int overrideDrive;

//change if necessary
int DEADZONE = 20;

//Drive Functions:

//Note: This drive applies for a 4 motor standard drive or tank drive.

//This sets all of your drive variables. Change ports if necessary
void driveVariables()
{
	driveY = vexRT[Ch3]; //forward movement.
	driveX = vexRT[Ch4] + vexRT[Ch1]; //turn movement.
	overrideDrive = vexRT[Btn7U]; //Override for Anti-Tip.
}

// This function is essentially a shortcut for our drive code.
// It sets the left and right motors to the left and right side
// of the robot, respectively.
// Change the names or amount of motors if necessary.
void updateDriveMotors(int left, int right)
{
	motor[front_right_drive] = right;
	motor[front_left_drive] = left;
	motor[back_left_drive] = left;
	motor[back_right_drive] = right;
}

//This function allows you to clear your integrated encoders.
//Change the names or amount of integrated encoders if necessary.
void clearIntegratedEncoders()
{
	nMotorEncoder[back_left_drive] = 0;
	nMotorEncoder[back_right_drive] = 0;
}

//Directional Drive set
int setForward(int forVal)
{
	if(abs(forVal) > DEADZONE)
	{
		forward = forVal;
	}
	else
	{
		forward = 0;
	}
	return forward;
}

int setTurn(int turnVal)
{
	if(abs(turnVal) > DEADZONE)
	{
		turn = (turnVal)*0.5;
	}
	else
	{
		turn = 0;
	}
	return turn;
}

//Regular Drive Set
void tankDrive(int forInput, int turnInput, int strafeInput)
{
	setForward(forInput);
	setTurn(turnInput);

	motor[front_left_drive] = forward + turn; //testing for better turn and strafe
	motor[front_right_drive] = forward - turn;
	motor[back_left_drive] = forward + turn;
	motor[back_right_drive] = forward - turn;
}



//Drive w/ Kamen Anti-Tip®
//Change the name of the gyro/motors if necessary.
void tankDriveKAT(int forInput, int turnInput, int strafeInput)
{
	setForward(forInput);
	setTurn(turnInput);

	if(SensorValue[vertGyro] < 100 && SensorValue[vertGyro] > -100)
	{
		motor[front_left_drive] = forward + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward - turn;
		motor[back_left_drive] = forward + turn;
		motor[back_right_drive] = forward - turn;
	}

	//KAT: Kamen Anti-Tip
	else if(SensorValue[vertGyro] >= 100 && overrideDrive == 0)
	{
		updateDriveMotors(-125,-125);
	}
	//SensorValue[vertGyro] = 0;
	else if(SensorValue[vertGyro] <= -100 && overrideDrive == 0)
	{
		updateDriveMotors(125,125);
	}
	//SensorValue[vertGyro] = 0;
	else if(overrideDrive == 1)
	{
		motor[front_left_drive] = forward + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward - turn;
		motor[back_left_drive] = forward + turn;
		motor[back_right_drive] = forward - turn;
		SensorValue[vertGyro] = 0;
		//updateDriveMotors(0,0);
	}
	else if(SensorValue[vertGyro] <= 100 && SensorValue[vertGyro] >= -100)
	{
		motor[front_left_drive] = forward + turn; //testing for better turn and strafe
		motor[front_right_drive] = forward - turn;
		motor[back_left_drive] = forward + turn;
		motor[back_right_drive] = forward - turn;
	}
}

//If you use the KAT, you MUST use the following function.
//It will prevent the gyro from taking control of the robot.
void gyroClearLoop(string gyro)
{
	static int stable = nPgmTime;
	if(abs(SensorValue[gyro]) > 100) stable = nPgmTime;
	if((nPgmTime - stable) == 5000) SensorValue[gyro] = 0;
}
