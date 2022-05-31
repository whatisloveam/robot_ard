void motorC(int power) // -255  -  255
{
	power = constrain(power, -255, 255);
	if(power > 0) //forward
	{
		digitalWrite(4, 0);
		analogWrite(5, power);
	}
	else
	{
		digitalWrite(4, 1);
		analogWrite(5, 255+power);
	}
}

void motorB(int power) // -255  -  255
{
	power = constrain(power, -255, 255);
	if(power > 0) //forward
	{
		digitalWrite(7, 0);
		analogWrite(6, power);
	}
	else
	{
		digitalWrite(7, 1);
		analogWrite(6, 255+power);
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
