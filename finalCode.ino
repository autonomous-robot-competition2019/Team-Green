
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

  // Set game state to findSide
  gameState = mFindSide;

  // Pixy
  pixy.init();

  // Look for Quaffles
  target_color = 3;
}

void loop() {

  // Act according to gameState
  switch(gameState) {
    case mSearch:
      break;
    case mFindGoal:
      break;
    case mShooting:
      break;
    case mFindSide:
      break;
    case mAvoidColl:
      break;
  }
}
