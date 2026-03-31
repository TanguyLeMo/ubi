#include <Arduino_LSM6DSOX.h>
#include <WiFiNINA.h>
#include <MadgwickAHRS.h>
#include <PDM.h>
Madgwick madgwick_filter;
float accelScale, gyroScale;
int counter;

static const char channels = 1;
static const int frequency = 20000;
short sampleBuffer[512];
volatile int samplesRead;

void setup()
{
//Gyroscope setup
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  Serial.begin(1200);
  while (!Serial)
    ;

  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

madgwick_filter.begin(IMU.gyroscopeSampleRate());
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
  Serial.println();

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println("Hz");
  Serial.println();

  pinMode(LEDB, OUTPUT);
  while (!Serial);
 
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }
}

  


void loop()
{

  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
  int temperature;
  bool alert = false;

  // read raw data from IMU
  IMU.readAcceleration(ax, ay, az);
  IMU.readGyroscope(gx, gy, gz);

  // convert from raw data to gravity and degrees/second units
  madgwick_filter.updateIMU(gx, gy, gz, ax, ay, az);
  if (IMU.temperatureAvailable())
  {
    IMU.readTemperature(temperature);
  }

  roll = madgwick_filter.getRoll();
  pitch = madgwick_filter.getPitch();
  heading = madgwick_filter.getYaw();

  if (temperature - 10 < 20 || temperature - 10 > 32 || pitch < -15 || pitch > 15)
  {
    alert = true;
  }
  int avg = 0;
  if (samplesRead)
  {
    long sum = 0;
    for (int i = 0; i < samplesRead; i++) 
    {
      sum += abs(sampleBuffer[i]);
    }
     avg = sum / samplesRead;
    if (avg > 1000)
    {
      alert = true;
    }
    samplesRead = 0;
  }

  if (counter % 50 == 0)
  {
    Serial.print("Mic avg: ");
    Serial.print(avg);
    Serial.print(" ");
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);
    // Print the temperature to the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    counter = 0;
  }

  if (alert)
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
  }
  else
  {
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, HIGH);
  }
  counter++;
}

void onPDMdata() {
  int bytesAvailable = PDM.available();
  PDM.read(sampleBuffer, bytesAvailable);
  samplesRead = bytesAvailable / 2;
}
