
#include "myHeader.h"



void setup() {
  // DC Motor setup
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  // Servo setup
  leftWheel.attach(left_motor);
  rightWheel.attach(right_motor);
  spinner.attach(spin);
  stopper.attach(stop);
  
}

void loop() {
  spinUp(200);
}
