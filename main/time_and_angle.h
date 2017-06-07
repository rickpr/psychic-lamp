#include "data.h"

int check_time() {
  return (2 * hour() + (minute() >= 30 ? 0.5 : 0)) - 11;
}

double vectors_to_phi(double x, double y, double z) {
  return atan(sqrt(x * x + y * y) / z);
}

double vectors_to_theta(double x, double y, double z) {
  return atan(y / x);
}

double vectors_to_rho(double x, double y, double z) {
  return sqrt(x * x + y * y + z * z);
}

double get_phi(Adafruit_LSM303_Accel_Unified accel, int number_of_samples, int sample_time_interval) {
  int accel_x[number_of_samples]; // 10 x-axis samples
  int accel_y[number_of_samples]; // 10 y-axis samples
  int accel_z[number_of_samples]; // 10 z-axis samples

  /*
   * SENSOR READINGS
   * Take 10 sample readings from the accelerometer, and take the average
   */
  int x = 0; // x-axis
  int y = 0; // y-axis
  int z = 0; // z-axis
  int i;

  for(i = 0; i < number_of_samples; i++) {
    // Get a new sensor event
    sensors_event_t event;
    accel.getEvent(&event);
    // Display the results (acceleration is measured in m/s^2)
    accel_x[i] = event.acceleration.x;
    accel_y[i] = event.acceleration.y;
    accel_z[i] = event.acceleration.z;

    x += accel_x[i]; // Sum of the x-axis
    y += accel_y[i]; // Sum of the y-axis
    z += accel_z[i]; // Sum of the z-axis


    delay(sample_time_interval);
  }

  x /= number_of_samples; // Final value for x-axis
  y /= number_of_samples; // Final value for y-axis
  z /= number_of_samples; // Final value for z-axis
  return vectors_to_phi(x, y, z);
}

int seek_position(bool direction, bool afternoon, int movement_duration) {
  if(direction == afternoon) {
    forward(movement_duration); // Full speed forwards signal pushing the solar panel to the left(west) for 0.5 seconds
  } else {
    reverse(movement_duration); // Full speed backwards signal pulling the solar panel to the right(east) for 0.5 seconds
  }
}
