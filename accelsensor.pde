#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

// Assign a unique ID to this sensor at the same time
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(76527);

void setup(void) {
  // Initialise the sensor
  if(!accel.begin()) {
    exit(1);
  }
}

void loop(void) {
  // Get a new sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  // Display the results (acceleration is measured in m/s^2)
  event.acceleration.x;
  event.acceleration.y;
  event.acceleration.z;

  delay(500);
}
