#include "Tank_Drive_Library.h"
#include "Manipulator_Library.h"
#include "PID.h"

//Autonomous Functions

//Modify motor/sensor names if necessary

void Strafe(int speed)
{
	motor[front_right_drive] = speed;
	motor[front_left_drive] = -speed;
	motor[back_left_drive] = speed;
	motor[back_right_drive] = -speed;
}

void setArmUp(int angle, int speed)
{
	while(SensorValue[RightEncoder] < angle)
	{
		updateCatMotors(speed);
	}
	updateCatMotors(0);
}
/*How to use setArmUp:
Write setArmUp and then the desired value of the encoder and the desired speed of the motors*/

void setArmDown(int angle, int speed)
{
	while(SensorValue[RightEncoder] > angle)
	{
		updateCatMotors(-speed);
	}
	updateCatMotors(0);
}
/*How to use setArmDown:
Write setArmDown and then the desired value of the encoder and the desired speed of the motors*/

void driveStraight(int speed,int time)//set speed (-127 - 127) and then time (in milliseconds)
{
	updateDriveMotors(speed,speed);
	wait1Msec(time);
	updateDriveMotors(0,0);
}
/*How to use driveStraight:
Write driveStraight and then the desired speed. The time is amount it will be running.*/

void clearGyro()
{
	SensorValue[gyro] = 0;
	wait1Msec(20);
}

void releaseClaw()
{
	motor[left_claw_motor] = 85;
	motor[right_claw_motor] = 85;
	wait1Msec(300);
	motor[left_claw_motor] = 0;
	motor[right_claw_motor] = 0;
}

void setClawSpeed(int speed)
{
	motor[left_claw_motor] = speed;
	motor[right_claw_motor] = speed;
}
/*How to use setClawSpeed:
Write setClawSpeed and then the motor speed.*/

//managed dynamic acceleration profile:
int rampDown(int speed, int cycle, int increment)
{
	for(int robotSpeed = 0; robotSpeed < 30; robotSpeed++)
	{
		updateDriveMotors(speed = speed - increment,speed = speed - increment);
		previousSpeed = robotSpeed;
		wait1Msec(50);//wait for update loop
	}
	if(speed < 0)
	updateDriveMotors(0,0);
	return previousSpeed;
}
/*How to use rampDown:
Write rampDown and then the speed amount, amount of cycles you want the code to run, and then the increment amount.
(Default should be (127,30,2))
You can also write previousSpeed for the speed amount if this is following a rampUp.*/

int rampUp(int speed,int cycle,int increment)
{
	for(int robotSpeed = 0; robotSpeed < cycle; robotSpeed++)
	{
		updateDriveMotors(speed = speed + increment,speed = speed + increment);
		previousSpeed = speed;
		wait1Msec(50);//wait for update loop
	}
	//updateDriveMotors(127,127);
	return previousSpeed;
}
/*How to use rampUp:
Write rampUp and then the speed amount, amount of cycles you want the code to run, and then the increment amount.
(Default should be (30,30,2))
You can also write previousSpeed for the speed amount if this is following a rampDown.*/

void accelerate(int speed, int time)
{
	if(time<1000)
	time = 1000;
	rampUp(speed,13,3);
	wait1Msec(time - 1000);
	rampDown(previousSpeed,13,3);
	updateDriveMotors(0,0);
}
/*How to use accelerate:
Write accelerate and then the INITIAL speed amount followed by the amount of TOTAL time you want this to run.*/

/*-------------------------------------------------------------------------------------------------------*/

//Examples

void auto1()
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, "   Auto 1   ");

	//REPLACE WITH CODE
}

void PIDExample()
{
	displayLCDCenteredString(0, "Now Playing...");
	displayLCDCenteredString(1, " PID Example ");

	clearGyro();
	initPID(theGyro, 0.335, 0.23, 0.26, 200, 5000, 1800);
	while(theGyro.isMoving)
	{
		theGyro.currentValue = SensorValue(gyro);

		int motorValue = calcPID(theGyro);

		if(motorValue > 60)
		{
			motorValue = 60;
		}
		if(motorValue < -60)
		{
			motorValue = -60;
		}
		updateDriveMotors(-motorValue,motorValue);
		wait1Msec(40);
	}
	wait1Msec(100);
}
