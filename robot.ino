
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
	s1 = map(analogRead(A0), 1000, 30, 0, 100);
	s2 = map(analogRead(A1), 1000, 30, 0, 100);
}
int pos = 0;
void setup()
{
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
  gyrosetup();
  turnwithgyro(-90);
  turnwithgyro(90);
  motorC(0);
  motorB(0);
  //turnwithgyro(-270);
  //turnwithgyro(0);
}



void loop()
{	
	gyrogetdata();
  
  //turnwithgyro(-180);
  //turnwithgyro(-270);
  //turnwithgyro(0);
}

void turnwithgyro(int angle)
{
  yaw = 0;
  int u;
  int err, errold;
  int P;
  int D;
  float I = 0;
  unsigned long t_entry = millis();

  while(true)
  {
    
    gyrogetdata();
    err = pos - angle;
    P = err * 3;
    I += err * 0.01;
    D = (err - errold)*10;
    Serial.print(P);
    Serial.print("\t");
    Serial.print(I);
    Serial.print("\t");
    Serial.println(D);
    u = P + I + D;
    u = constrain(u, -120, 120);
    motorB(u);
    motorC(-u);
    errold = err;
    if((abs(err) <= 3 && abs(D) <= 2) || 
       (millis() - t_entry > 2000)) break;
    delay(10);
  }
  
  
}
