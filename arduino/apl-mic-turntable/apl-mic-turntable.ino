/*
Author: Bogdan Bacila 
        Applied Psychoacoustics Lab, University of Huddersfield, UK 
*/

#include <Arduino.h>
#include <SoftwareSerial.h>

// You need to have the StepperDriver library installed
// Tools -> Manage Libraries -> Search for "stepperDriver"
// Make sure the author is "Laurentiu Badea" 
// Version number: 1.3.1
// Alternatively, this is the library repo: https://github.com/laurb9/StepperDriver
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Define motor speed
#define RPM 5

// Stepper driver used in this case: TMC2100. 
// Useful resource for wiring up the motor to the Arduino: https://electropeak.com/learn/interfacing-tmc2100-stepper-motor-driver-with-arduino/
// Please make sure the stepper driver is connected properly to both the Arduino and the motor to avoid damage of any of the parts. 
// Since microstepping is set externally, make sure this matches the selected mode on your stepper driver
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step, 4=quarter step, etc.
#define MICROSTEPS 16

// digital outputs connecting to the stepper driver. 
#define DIR_PIN 2
#define STEP_PIN 3

// add stepper motor instance.
// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

// This device is configured to work with a HC-06 Bluetooth module as a receiver for serial messages.
// A comprehensive guide for connecting and configuring the HC-06 can be read here: https://www.aranacorp.com/en/arduino-and-bluetooth-module-hc-06/
// We use software serial here instead of Arduino's hardware serial as this allows for programming it without disconnecting the bluetooth module. 
// Connect the Arduino RX on pin 4 to the HC-06 TX.
// Connect the Arduino TX on pin 5 to the HC-06 RX through a voltage divider.
SoftwareSerial BTserial(4,5); // RX | TX

//declare variables
String inString = "";
float angle;
bool sendFlag = false;

void setup() {
  BTserial.begin(9600);
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);
}

void loop() {
  
  // read the incoming serial messages - this is how we communicate the rotation angle and direction
  // e.g.:    "5" - rotates 5 degrees clockwise
  //         "-5" - rotates 5 degrees counter-clockwise 
  //        "2.5" - rotates 2.5 degrees clockwise
  //       "-2.5" - rotates 2.5 degrees counter-clockwise 
  while (BTserial.available() > 0) {
    int inChar = BTserial.read();

    if (inChar != '\n') {

      // As long as the incoming byte
      // is not a newline,
      // convert the incoming byte to a char
      // and add it to the string
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then convert the string's value to a float:
    else {
      angle = inString.toFloat();
      sendFlag = true;
      inString = "";
    }
  }

  //rotate motor to the desired angle and direction
  if (sendFlag){  
    stepper.rotate(angle);
    sendFlag = false;
    delay(1000); 
  }
        
}
