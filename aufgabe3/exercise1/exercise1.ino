#include <WiFiNINA.h>

const int buttonPin = 2;
int buttonState = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  if(Serial.available() > 0){
    char receved = Serial.read();
    if(receved == '1'){
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH);
    }
    else if(receved == '0'){
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, LOW);
    }
  }
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    Serial.write('1');
  } else {
    Serial.write('0');
  }
}
