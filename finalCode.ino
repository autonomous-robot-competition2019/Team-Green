
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

  // Look for Quaffles to start
  target_color = 3;
}

void loop() {

  int irVal = analogRead(ir_sensor);
    
  // Act according to gameState
  switch(gameState) {

    // Searching for quaffles and picking them up
    case mSearch:
      int dir = findClosestQuaffle();
      quaffleSearch(dir);
      break;

    // Finding goal so we can shoot
    case mFindGoal:
      break;

    // Shooting  
    case mShooting:
       // If we are just starting to shoot, start timer  
      if (!isShooting) {
          isShooting = 1;
          start = millis();
      }
      
      unsigned long timeElapsed = millis() - start;
      
      if (timeElapsed > 35000) {
        gameState = mSearch;
        isShooting = 0;
        break;
      }
      else {
        spinUp(225);
        spinner.write(120);
      }
    
    // Figuring out whoch side we are on at the beginning 
    case mFindSide:
      // Rotate to the side then move forwards
      drive(90,95); // turn left
      delay(2000);

      drive(100,100); // go forward
      delay(2000);

      drive(95,90); // turn back to the right
      delay(2000);

      drive(95,95); // go straight

    // Avoid collision
    case mAvoidColl:
      drive (85,85);
      delay(1000);
      
      while (irVal > threshold) {
          irVal = analogRead(ir_sensor);
          drive(90,95);
      }
      gameState = previousState;
      break;
  }
}
