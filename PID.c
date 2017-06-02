//void InitEffector(controlPID_t thisPID)
//{
//	thisPID.currentValue = 0;
//	int targetValue = 0;
//	int error;
//	int previousError;
//	bool isMoving;
//	float Kp;
//	float Ki;
//	float Kd;
//	unsigned int waitTime;
//	unsigned int timeout;
//	unsigned long startPGMTime;
//	unsigned long stableTime;

//}

void initPID(controlPID_t thisPID, float Kp, float Ki, float Kd, int waitTime, int timeout, int targetValue)
{
	thisPID.currentValue = 0;
	thisPID.previousValue = 0;
	thisPID.previousValueTime = nPgmTime;
	thisPID.velocity = 0;
	thisPID.targetValue = targetValue;
	thisPID.error = 0;
	thisPID.previousError = 0;
	thisPID.integralRaw = 0;
	thisPID.isMoving = false;
	thisPID.Kp = Kp;
	thisPID.Ki = Ki;
	thisPID.Kd = Kd;
	thisPID.waitTime = waitTime;
	thisPID.timeout = timeout;
	thisPID.startPGMTime = nPgmTime;
	thisPID.stableTime = nPgmTime;

	thisPID.isMoving = true;

	writeDebugStreamLine("error, proportional, integral, derivative, currentValue, targetValue, finalPower");
}

int calcPID(controlPID_t thisPID)
{
	// Clear flag if we are stable for the waitTime
	if((nPgmTime - thisPID.stableTime) > thisPID.waitTime)
	{
		thisPID.isMoving = false;
	}

	thisPID.error = thisPID.targetValue - thisPID.currentValue;

	// Compute Proportional
	int proportional = thisPID.error * thisPID.Kp;

	// Compute Integral
	int integral;
	int integralActiveZone = 20;
	int integralRawLimit = 60000/thisPID.Ki;
	int derivative;

	if(abs(thisPID.error) < integralActiveZone && thisPID.error != 0)
	{
		thisPID.integralRaw += thisPID.error;
	}
	else
	{
		thisPID.integralRaw = 0;
	}

	//if (thisPID.integralRaw > integralRawLimit) thisPID.integralRaw = integralRawLimit;
	//if (thisPID.integralRaw < -integralRawLimit) thisPID.integralRaw = -integralRawLimit;

	integral = thisPID.integralRaw * thisPID.Ki;

	// Calculate Derivative
	derivative = thisPID.Kd * (thisPID.error - thisPID.previousError);
	thisPID.previousError = thisPID.error;

	if (thisPID.error == 0)
	{
		derivative = 0;
	}

	// Set motor
	int finalPower = proportional + integral + derivative;

	if(abs(thisPID.error) > 80) thisPID.stableTime = nPgmTime;

	// Logging....
	writeDebugStreamLine("%d,%d,%d,%d,%d,%d,%d", thisPID.error, proportional, integral, derivative, thisPID.currentValue, thisPID.targetValue, finalPower);

	return finalPower;
}

void SetTimeRun(controlPID_t thisPID, int timeValue)
{
	thisPID.startPGMTime = nPgmTime;
	thisPID.stableTime = nPgmTime;
	thisPID.timeout = timeValue;

	thisPID.isMoving = true;
}

void doTimeRun(controlPID_t thisPID)
{
	// Quit moving when we timeout on the maneuver
	if (nPgmTime > (thisPID.startPGMTime + thisPID.timeout))
	{
		thisPID.isMoving = false;
	}
}
