
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
#define RPM 5

// Since microstepping is set externally, make sure this matches the selected mode on your stepper driver
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step, 4=quarter step, etc.
#define MICROSTEPS 16

// digital outputs connecting to the stepper driver. 
#define DIR_PIN 2
#define STEP_PIN 3

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);

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
    // then the string's value as a float:
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
