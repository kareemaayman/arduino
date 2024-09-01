#include <Wire.h>

// MPU6050 I2C address
const int MPU6050_ADDR = 0x68;

// Registers
const int PWR_MGMT_1 = 0x6B;
const int GYRO_XOUT_H = 0x43;
const int GYRO_YOUT_H = 0x45;
const int GYRO_ZOUT_H = 0x47;

// Sensitivity scale factor for the gyroscope
const float GYRO_SENSITIVITY = 131.0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  // Wake up MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0);  // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  // Read gyroscope data for Z-axis (Yaw)
  int16_t gyroZ = readMPU6050(GYRO_ZOUT_H);

  // Convert to degrees/second
  float yaw = gyroZ / GYRO_SENSITIVITY;

  // Print Yaw value
  Serial.print("Yaw: ");
  Serial.println(yaw);
  
  delay(100);
}

int16_t readMPU6050(int reg) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 2, true);

  int16_t value = (Wire.read() << 8) | Wire.read();
  return value;
}