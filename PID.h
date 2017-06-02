typedef struct
{
	int currentValue;
	int previousValue;
	int previousValueTime;
	float velocity;
	int targetValue;
	int error;
	int previousError;
	int integralRaw;
	bool isMoving;
	float Kp;
	float Ki;
	float Kd;
	unsigned int waitTime;
	unsigned int timeout;
	unsigned long startPGMTime;
	unsigned long stableTime;
} controlPID_t;

//void InitEffector(controlPID_t thisEffector);

void initPID(controlPID_t thisPID, float Kp, float Ki, float Kd, int waitTime, int timeout);
int calcPID(controlPID_t thisPID);

void SetTimeRun(controlPID_t thisPID, int timeValue);
int doTimeRun(controlPID_t thisPID);

#include "PID.c"

/*
PID Code dedicated to Qusai for keeping us all in check and creating the best Engineering Notebook in the league..
*/
