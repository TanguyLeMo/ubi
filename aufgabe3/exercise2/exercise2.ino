#include <WiFiNINA.h>
#include <Arduino_LSM6DSOX.h>
void setup() {
  // put your setup code here, to run once:
  if(!IMU.begin())
  {
    Serial.println("failed to init IMU");
  }
  if(!IMU.temperatureAvailable())
  {
    Serial.println("PROBLEMS, ALWAYS");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int current_temp = 0;
  static int prev_temp = 0;
  IMU.readTemperature(current_temp);
  if(current_temp != prev_temp){
    Serial.println(current_temp);
  }
  prev_temp = current_temp; 
}

