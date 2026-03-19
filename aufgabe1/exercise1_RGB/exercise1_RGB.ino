#include <WiFiNINA.h>
void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDG, LOW); 
  digitalWrite(LEDR, HIGH); 
  delay(500);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, HIGH);
  delay(500);
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDG, HIGH);
  delay(500);
}
