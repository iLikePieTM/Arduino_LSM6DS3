/*
  Arduino LSM6DS3 - Simple Temperature Sensor

  This example reads the temperature values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 15 Mar 2020
  by Alex Hoppe

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Temperature sensor sample rate = ");
  Serial.print(IMU.temperatureSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Temperature readings in degrees C");
  Serial.println();
}

void loop() {
  float t;          // To store temperature readings
  float t_sum = 0;  // To store the readings sum
  int i = 0;        // To count the readings

  while (i < 100) {
    if (IMU.temperatureAvailable()) {
      // After IMU.readTemperature() returns, t will contain the temperature reading
      IMU.readTemperature(t);
      // Add the reading to the sum and increase the counter
      t_sum += t;
      i++;
    }
  }
  // Print the averaged value (for smoothing)
  Serial.print("T = ");
  Serial.print(t_sum/i);
  Serial.println(" °C");
}
