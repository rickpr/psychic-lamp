/*
   This program i designed to test the functionality of the Arduino with the
   WASP and actuator.

   Hardware used:
   1 x Arduino Uno
   1 x WASP Motor Controller
   1 x PA-09-12-300 Linear Actuator
 */
/*
   SERVO LIBRARY

   Include the Servo library and create the servo object.
 */

#include <Servo.h>
#include <Wire.h>
#include <string>
Servo myservo; // Create servo object to control a servo

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
}

void loop() {
  /*
     SOLAR PANEL MOVEMENT
   */
  myservo.writeMicroseconds(2000); // Full speed forwards
  delay(500); //0.5 seconds
  myservo.writeMicroseconds(1000); // Full speed backwards
  delay(500); //0.5 seconds
  myservo.writeMicroseconds(1520); // Stationary (1520) signal stop the solar panel from moving
  delay(2000); // Delay before another test
}
