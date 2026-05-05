#include <WiFiNINA.h>

const int buttonPin = 2;
PinStatus buttonState = LOW;
void setup() {
  Serial.begin(9600);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  static PinStatus previous = LOW;

  if(Serial.available() > 0){
    char received = Serial.read();

    if(received == '1'){
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH);
    }
    else if(received == '0'){
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, LOW);
    }
  }
  buttonState = digitalRead(buttonPin);
  if (buttonState != previous) {
    if(buttonState == LOW ){
      Serial.print('1');
      Serial.print('\n');
    } else {
      Serial.print('0');
      Serial.print('\n');
    }
    previous = buttonState;
  }
}
