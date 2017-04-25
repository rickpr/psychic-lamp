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
#include "Adafruit_Sensor.h"
#include "Adafruit_LSM303_U.h"

Servo myservo; // Create servo object to control a servo
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
  if(!accel.begin()) {
    exit(1);
  }
  Serial.begin(57600);
//  DateTime.sync(0);
}

void loop() {

  /*
     SOLAR PANEL MOVEMENT
     The solar panel will tilt toward west if the sunlight intensity detected on
     the west side of the panel is greater than the one detected on the east
     side. The solar panel will tilt toward east if the sunlight intensity
     detected on the east side is greater than the one detected on the west
     side. However, if the readings from both side are similar, the solar panel
     will remain stationary.
   */
    // Get a new sensor event
    sensors_event_t event;
    accel.getEvent(&event);
  if(event.acceleration.y > 1) { // If the angle is greater than phi
    myservo.writeMicroseconds(2000); // Full speed forwards (2000) signal pushing the solar panel to the left(west)
    delay(50); //0.5 seconds
  } else if(event.acceleration.y < -1) { // If the angle is greater than phi
    myservo.writeMicroseconds(1000); // Full speed backwards (1000) signal pulling the solar panel to the right(east)
    delay(50); //0.5 seconds
  } else { // If the sunlight intensity is similar from both side of the panel
    myservo.writeMicroseconds(1520); // Stationary (1520) signal stop the solar panel from moving
    delay(50);
  }
}
