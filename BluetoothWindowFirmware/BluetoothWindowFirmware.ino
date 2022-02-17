/*
 * M5 Bluetooth Window Demo
 * Revitalised old SDP project in M5's Great Room
 * Authors: Akshat Sahay, Cobie Yung
 */

#include <Stepper.h>

/*
 * The Feather 328P is the main controller for this project.
 * It connects to an HC-05 Bluetooth module and an L298N motor driver. 
 * 
 * The HC-05 connects to an Android app and gets a single character over Bluetooth.
 * This character sets the state, which determines whether the window goes up or down. 
 * 
 * The L298N motor driver is controlled using the Stepper library. 
 * It connects to a stepper motor attached to the window, which enables the window to move.
 */

const int stepsPerRevolution = 500; // number of revolutions for stepper in one motion 
bool state = false;                 // current state of stepper 
bool prevState = false;             // previous state of stepper 
 
// create instance of Stepper library
Stepper myStepper(stepsPerRevolution, 10, 9, 6, 5);

void setup() {
  myStepper.setSpeed(20); // set the speed at 60 rpm 
  Serial.begin(9600);     // initialize the serial port
  pinMode(13, OUTPUT);    // set pin 13 as an OUTPUT
}

void loop() {
  if(Serial.available()) {
    // set the state to respond to new input 
    if(Serial.parseInt() == 1) {
      // if received a 1, reset state 
      if(state == true) state = false; 
      else state = true; 
    }
  }

  if(state != prevState) {
    if(state == true) {
      // motor moves clockwise
      digitalWrite(13, HIGH); 
      myStepper.step(stepsPerRevolution);
      prevState = true; 
    }

    else {
      // motor moves counterclockwise 
      digitalWrite(13, LOW); 
      myStepper.step(-stepsPerRevolution);
      prevState = false; 
    }
  }
}
