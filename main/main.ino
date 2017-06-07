/*
   This program will allow the solar panel to track the sun, and drive the
   actuator using pwm. Readings from an accelerometer will be taken from 
   the solar panel.  A number of samples will be taken, and a average
   reading will be calculated in order to determine the angle of the solar
   panel. The linear actuator will then either extend or retract to
   angle the solar panel so it is facing the sun.

   Hardware used:
   1 x Arduino Uno
   1 x WASP Motor Controller
   1 x PA-09-12-300 Linear Actuator
   1 x Adafruit LSM303
 */
/*
   SERVO LIBRARY

   Include the Servo library and create the servo object.
 */

#include <Servo.h>
#include <Wire.h>
#include <Time.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_LSM303_U.h"
#include "movement_helpers.h"
#include "time_and_angle.h"
#include "calibrate.h"

// Servo myservo; // Create servo object to control a servo
// Assign a unique ID to this sensor at the same time
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(76527);

/*
 * PIN ASSIGNMENTS
 * Assign pins from WASP Controller and Arduino Micro to appropriate variable.
 */

const int WASP_Power  = 10; // Assign pin 10 to Power for the WASP
const int WASP_Ground = 11; // Assign pin 11 to Ground for the WASP

/*
 * VARIABLE DECLARATION
 * Declare and initialize variables that will be used in the functions later
 */

const int number_of_samples = 10;
int accel_x[number_of_samples]; // 10 x-axis samples
int accel_y[number_of_samples]; // 10 y-axis samples
int accel_z[number_of_samples]; // 10 z-axis samples
const int sample_time_interval = 10000; // Change this value to set the interval between each sample is taken (ms)
const long solar_panel_adjustment_interval = 600000; // Change this value to set the interval between each adjustment from the solar panel (ms)
const int initial_adjustment_time = 512; // The amount of time to move the panel the first time to aim for the correct angle
const float threshold = 0.1; // The amount of radians considered to be within the target range
const int give_up = 100; // The amount of times to attempt to correct the angle before giving up

double current_time  = 0;
int current_increment = check_time();
bool afternoon = false;

void setup() {
  /*
   * SET INPUT & OUTPUT
   * Set the input and output to the variables and pins.
   */

  myservo.attach(9);                // Attaches the servo on pin 9 to the servo
  pinMode(WASP_Power, OUTPUT);      // Set Power to output
  pinMode(WASP_Ground, OUTPUT);     // Set Ground to output
  digitalWrite(WASP_Power, HIGH);   // Set 5V to pin 10
  digitalWrite(WASP_Ground, LOW);   // Set GND to pin 11
  // Initialize the sensor
  if(!accel.begin())
    exit(1);

  Serial.begin(57600);
  calibrate_end();
  calibrate_start();
}

void loop() {
  current_increment = check_time();
  if(current_increment >= 16)
    afternoon = true;

  /*
   * SENSOR READINGS
   * Take 10 sample readings from the accelerometer, and take the average
   */
  // int x = 0; // x-axis
  // int y = 0; // y-axis
  // int z = 0; // z-axis
  // int i;
  // double phi; // Angle phi
  // double theta; // Angle theta
  // double rho; //Magnitude rho


  /*
     SOLAR PANEL MOVEMENT
     The solar panel will tilt if the angle of the panel is greater
     than the margin of error.
   */

  int movement_duration = initial_adjustment_time;
  double phi = get_phi(accel, number_of_samples, sample_time_interval);
  double angle_difference = phi - sun_angles[current_increment];
  bool direction = angle_difference > 0;
  bool new_direction = direction;
  int attempt_count = 0;
  while(attempt_count < give_up && abs(angle_difference) > 0.1 && movement_duration) {
    seek_position(direction, afternoon, movement_duration);
    delay(1000); // Delay a second so the actuator has time to settle
    phi = get_phi(accel, number_of_samples, sample_time_interval);
    angle_difference = phi - sun_angles[current_increment];
    new_direction = angle_difference > 0;
    if(new_direction != direction)
      movement_duration /= 2;
    direction = new_direction;
  }
  delay(solar_panel_adjustment_interval); // Delay before another adjustment will be made
}
