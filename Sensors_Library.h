//SENSOR VARIABLES
/*
potentiometer
gyro
encoder
sonar
integrated encoders
lcd
accelerometer
touch
line follower
*/

//change names if necessary
int getGyro()
{
	return SensorValue[gyro];
}

int getPot()
{
	return SensorValue[potentiometer];
}

int getEnc()
{
	return SensorValue[encoder];
}

int getIntEnc()
{
	return nMotorEncoder[motor_name];
	//It must be the name of the motor which the encoder is connected to.
}

int getAccelerometerAxisX()
{
	return SensorValue[accelerometerX];
}

int getAccelerometerAxisY()
{
	return SensorValue[accelerometerY];
}

int getAccelerometerAxisZ()
{
	return SensorValue[accelerometerZ];
}

bool getTouch()
{
	return SensorValue[touch];
}

int getLineFollow()
{
	return SensorValue[lineFollow];
}

void lcd_example()//FOR EXAMPLE SAKE ONLY! DO NOT USE!
{
	//use the following LCD code examples in the MAIN file

	//Basic
	displayLCDString(0, 0, "Insert Text Here");
	//displayLCDString(Line Number,Position, "Text");

	//Centered
	displayLCDCenteredString(0, "Insert Text Here");
	//displayLCDCenteredString(Line Number, "Text");

	//displaying a sensor or variable value
	//Begin by creating certain strings inside the usercontrol loop but outside the while:
	string mainBattery;

	//continue by writing the following:
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	//Change this last couple parts out with the variable/sensor.
	displayNextLCDString(mainBattery);
}
