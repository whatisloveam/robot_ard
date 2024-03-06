void motorC(int power) // -255  -  255
{
	power = -constrain(power, -255, 255);
	if(power > 0) //forward
	{
		digitalWrite(9, 0);
		analogWrite(10, power);
	}
	else
	{
		digitalWrite(9, 1);
		analogWrite(10, 255+power);
	}
}

void motorB(int power) // -255  -  255
{
	power = -constrain(power, -255, 255);
	if(power > 0) //forward
	{
		digitalWrite(12, 0);
		analogWrite(11, power);
	}
	else
	{
		digitalWrite(12, 1);
		analogWrite(11, 255+power);
	}
}

void brake()
{
	motorB(0);
	motorC(0);
	delay(300);
}

void moveForTime(int power, int t)
{
	motorB(power);
	motorC(power);
	unsigned long tExit = millis() + t;
	while(millis() < tExit);
	brake();
}

void motorBForTime(int powerB, int t)
{
	motorB(powerB);
	unsigned long tExit = millis() + t;
	while(millis() < tExit);
	brake();
}

void motorCForTime(int powerC, int t)
{
	motorC(powerC);
	unsigned long tExit = millis() + t;
	while(millis() < tExit);
	brake();
}
