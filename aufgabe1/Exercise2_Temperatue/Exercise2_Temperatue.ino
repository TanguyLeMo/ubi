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
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int current_temp = 0;

  IMU.readTemperature(current_temp);
  Serial.println(current_temp);
  if (current_temp > 32)
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDR, HIGH); 
  } else if (current_temp < 20)
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    di1italWrite(LEDB, LOW);
    digitalWrite(LEDR, HIGH); 
  } 
  else 
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, HIGH);
  }
  delay(250);
}
