
// github.com/whatisloveam/robot_ard

int s1, s2;
float yaw = 0;

void PAction() {
	upd();
	int u = 0.3 *(s1 - s2);
	motorB(150 + u);
	motorC(150 - u);
	delay(10);
}
void line() {
	while(true) PAction();
}
void lineForCross() {
	upd();
	while(!(s1 < 45 && s2 < 45)) PAction();
}
void upd() {
	s1 = map(analogRead(A1), 1000, 30, 0, 100);
	s2 = map(analogRead(A2), 1000, 30, 0, 100);
}
int pos = 0;
void setup()
{
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
  Serial.begin(57600);
  while(analogRead(A0) < 512);
  /*moveForTime(100, 500);
  motorBForTime(100, 500);
  moveForTime(100, 500);
  motorBForTime(100, 500);
  moveForTime(100, 500);
  motorBForTime(100, 500);
  moveForTime(100, 500);*/
}

void loop()
{	
	upd();
  Serial.print(s1);
  Serial.print("\t");
  Serial.println(s2);
  delay(10);
}
