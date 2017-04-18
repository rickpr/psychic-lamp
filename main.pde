/*
   This program will allow the solar panel to track the sun, and drive the
   actuator using pwm. Readings from an accelerometer will be taking from 
   the solar panel.  A number of samples will be taken, and a average
   reading will be calculated in order to determine the angle of the solar
   panel. The linear actuator will then either extend or retract to
   angle the solar panel so it is facing the sun.

   Hardware used:
   1 x Arduino Micro
   1 x WASP Motor Controller
   1 x PA-14-6-150 Linear Actuator
   2 x Photoresistors
   2 x 7k ohm Resistors
 */
/*
   SERVO LIBRARY

   Include the Servo library and create the servo object.
 */

#include
Servo myservo; // Create servo object to control a servo

/*
   PIN ASSIGNMENTS
   Assign pins from WASP Controller and Arduino Micro to appropriate variable.
 */

const int WASP_Power       = 10; // Assign pin 10 to Power for the WASP
const int WASP_Ground      = 11; // Assign pin 11 to Ground for the WASP
const int sensor_west_pin1 =  7; // A7 pin 6 sensor input 1 west
const int sensor_east_pin2 =  8; // A8 pin 8 sensor input 2 east

/*
   VARIABLE DECLARATION

   Declare and initialize variables that will be used in the functions later
 */

const int number_of_samples = 10;
int sensor_west[number_of_samples]; // 10 sample readings from sensor on the west side
int sensor_east[number_of_samples]; // 10 sample readings from sensor on the east side
int reset_counter = 0; // Time counter for resetting the solar panel position
const int sample_time_interval = 10000; // Change this value to set the interval between each sample is taken (ms)
const long solar_panel_adjustment_interval = 600000; // Change this value to set the interval between each adjustment from the solar panel (ms)

void setup() {

  /*
     SET INPUT & OUTPUT
     Set the input and output to the variables and pins.
   */

  myservo.attach(9);                // Attaches the servo on pin 9 to the servo
  pinMode(WASP_Power, OUTPUT);      // Set Power to output
  pinMode(WASP_Ground, OUTPUT);     // Set Ground to output
  digitalWrite(WASP_Power, HIGH);   // Set 5V to pin 10
  digitalWrite(WASP_Ground, LOW);   // Set GND to pin 11
  pinMode(sensor_west_pin1, INPUT); // Set sensor west pin to input
  pinMode(sensor_east_pin2, INPUT); // Set sensor east pin to input
}

void loop() {

  /*
     SENSOR READINGS
     Take 10 sample readings from both sensors, and take the average of the inputs.
   */

  int solar_input_west = 0; // Sun light intensity readings from sensor west
  int solar_input_east = 0; // Sun light intensity readings from sensor east
  int i;

  for(i = 0; i < number_of_samples; i++) {
    sensor_west[i] = analogRead(sensor_west_pin1); // Taking the analog readings from sensor west
    sensor_east[i] = analogRead(sensor_east_pin2); // Taking the analog readings from sensor east
    solar_input_west += sensor_west[i]; // Sum all the inputs from sensor west
    solar_input_east += sensor_east[i]; // Sum all the inputs from sensor east
    delay(sample_time_interval);
  }

  solar_input_west /= number_of_samples; // The average of input signals from sensor west
  solar_input_east /= number_of_samples; // The average of input signals from sensor east

  /*
     SOLAR PANEL MOVEMENT
     The solar panel will tilt toward west if the sunlight intensity detected on
     the west side of the panel is greater than the one detected on the east
     side. The solar panel will tilt toward east if the sunlight intensity
     detected on the east side is greater than the one detected on the west
     side. However, if the readings from both side are similar, the solar panel
     will remain stationary.
   */

  if(solar_input_west - solar_input_east > 20) { // If the sunlight intensity is higher on the west side of the panel
    myservo.writeMicroseconds(2000); // Full speed forwards (2000) signal pushing the solar panel to the left(west)
    delay(500); //0.5 seconds
  } else if(solar_input_east - solar_input_east > 20) { // If the sunlight intensity is higher on the east side of the panel
    myservo.writeMicroseconds(1000); // Full speed backwards (1000) signal pulling the solar panel to the right(east)
    delay(500); //0.5 seconds
  } else { // If the sunlight intensity is similar from both side of the panel
    myservo.writeMicroseconds(1520); // Stationary (1520) signal stop the solar panel from moving
  }
  delay(solar_panel_adjustment_interval); // Delay before another adjustment will be made
}
