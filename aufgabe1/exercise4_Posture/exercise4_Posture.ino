#include <Arduino_LSM6DSOX.h>
#include <WiFiNINA.h>
#include <MadgwickAHRS.h>

Madgwick filter;
int counter = 0;

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);

  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");

  filter.begin(IMU.gyroscopeSampleRate());
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
  int temperature = 0;
  bool alert = false;

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    filter.updateIMU(gx, gy, gz, ax, ay, az);

    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();

    
    IMU.readTemperature(temperature);
    temperature = temperature - 10;

    if (temperature < 20  || temperature  > 32 ) {
      alert = true;
    }
    if (pitch < -15 || pitch > 15)
    {
      alert = true;
    }
    if (roll < -20 || roll > 20 )
    {
      alert = true;
    }
    if (counter % 100 == 0) {
      Serial.print("Orientation: ");
      Serial.print(heading);
      Serial.print(" ");
      Serial.print(pitch);
      Serial.print(" ");
      Serial.println(roll);
      Serial.print(temperature);
      Serial.println(" °C");
    }
    if (alert)
    {
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, LOW);
    }
    else
    {
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDR, LOW);
    }
    counter++;
  }
}