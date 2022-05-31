#include <Wire.h>
const int MPU = 0x68;
float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float accXdeg, accYdeg, gyroXdeg, gyroYdeg, gyroZdeg;
float roll, pitch, yaw;

float accXerror, accYerror, gyroXerror, gyroYerror, gyroZerror;
float elTime, curTime, prevTime;

int c = 0;
void gyrosetup()
{
  pinMode (9, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  
  calibrateIMU();
  delay(20);
}
void gyrogetdata()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  
  accX = (Wire.read() << 8 | Wire.read()) / 16384.0;
  accY = (Wire.read() << 8 | Wire.read()) / 16384.0;
  accZ = (Wire.read() << 8 | Wire.read()) / 16384.0;
  
  accXdeg = (atan(accY / sqrt(pow(accX, 2) + pow(accZ, 2)))
        * 180 / PI) - 0.58;
  accYdeg = (atan(-1 * accX / sqrt(pow(accY, 2) + pow(accZ,2)))
        * 180 / PI) + 1.58;
  
  prevTime = curTime;
  curTime = millis();
  elTime = (curTime - prevTime) / 1000;
  
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  
  gyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
  gyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  gyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  
  gyroX += 1.54;
  gyroY += 1.29;
  gyroZ += 1.09;
  
  gyroXdeg += gyroX * elTime;
  gyroYdeg += gyroY * elTime;
  yaw += gyroZ * elTime;
  
  roll  = 0.96 * gyroXdeg + 0.04 * accXdeg;
  pitch = 0.96 * gyroYdeg + 0.04 * accYdeg;
  
//  Serial.print(roll);
//  Serial.print("\t");
//  Serial.print(pitch);
//  Serial.print("\t");
//  Serial.println(yaw);
  pos = yaw;
}

void calibrateIMU() {
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    accX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    accY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    accZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
  
    accXerror += ((atan((accY) / sqrt(pow((accX), 2) + pow((accZ), 2))) * 180 / PI));
    accYerror += ((atan(-1 * (accX) / sqrt(pow((accY), 2) + pow((accZ), 2))) * 180 / PI));
    c++;
  }
  accXerror /= 200;
  accYerror /= 200;
  c = 0;
  
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    gyroXerror += (gyroX / 131.0);
    gyroYerror += (gyroY / 131.0);
    gyroZerror += (gyroZ / 131.0);
    c++;
  }
  gyroXerror /= 200;
  gyroYerror /= 200;
  gyroZerror /= 200;
  
  Serial.print("AccErrorX: ");
  Serial.println(accXerror);
  Serial.print("AccErrorY: ");
  Serial.println(accYerror);
  Serial.print("GyroErrorX: ");
  Serial.println(gyroXerror);
  Serial.print("GyroErrorY: ");
  Serial.println(gyroYerror);
  Serial.print("GyroErrorZ: ");
  Serial.println(gyroZerror);
}
