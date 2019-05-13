
#include "myHeader.h"




void setup() {
  Serial.begin(9600);
  
  // DC Motor setup
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  // Servo setup
  //STOP: 90, 90
  //FORWARD: (90,180]
  //REVERSE: [0,90)
  //ROTATE LEFT: left wheel STOP, right wheel Forward
  leftWheel.attach(left_motor);
  rightWheel.attach(right_motor);
  spinner.attach(spin);
  stopper.attach(my_stop);

  // Start color sensor
  tcs.begin();

  // Initialize game
  gameState = START;
  start_time = millis();

  
  setGamma();

  // Run spinner
  spinner.write(140);

  // Initialize Pixy
  pixy.init();
}

void loop() {
  // Serial.println(gameState);
  Serial.println(analogRead(ir_sensor_center));
  // Check to see if game is done, if so set gameState to DONE
  float red,green,blue;
  tcs.getRGB(&red, &green, &blue);
  
  curTime = millis() - start_time;
  if (curTime >= 300000) gameState = DONE;
  //If sopmething is infront of the robot, back-up and turn.Unless gameState is SHOOTING
  collisionCheck(red,green,blue);

  // Act depending on gameState
  switch(gameState) {

    case DONE:
      drive(90,90);
      spinner.write(90);
      break;

    case START: 
       // Get RGB values from color sensor
      delay(60);  // takes 50ms to read
      tcs.getRGB(&red, &green, &blue);
      
      // Rotate to the side then move forwards
      drive(90,95); // turn left
      delay(2500);

      drive(100,100); // go forward
      delay(2000);

      drive(95,90); // turn back to the right
      delay(2700);

      drive(95,95); // go straight

      
      // Check to see if there is red or blue
     while (returnColor(red,green,blue) != RED_COLOR &&  returnColor(red,green,blue) != BLUE_COLOR) {
        delay(60);  // takes 50ms to read
        tcs.getRGB(&red, &green, &blue);
     }
     startSide = returnColor(red,green,blue);
    // Serial.print("Start Side: ");
    // Serial.println(startSide);
     drive(90,90);
     
      // If we find red or blue start searching for quaffles
     gameState = FIND;
     quaffle_start = millis();
     break;

      case FIND:
        quaffle_time = millis() - quaffle_start;

        // If time is up change to shooting mode
        if (quaffle_time > 120000) {
          gameState = FIND_GOAL;
          drive(90,90);
        } else {
        int closest_quaffle = findClosestQuaffle();
        // Serial.println(closest_quaffle);
        quaffleSearch(closest_quaffle);    
        }
        break;

      case FIND_GOAL: 

        int middle = isRedOrBlue();
        middleSearch(middle);       
        shooting_start = millis();
        gameState = SHOOTING;
        drive(90,90);
        break;

      case SHOOTING:
        shooting_time = millis() - shooting_start;
        if (shooting_time > 60000) {
          gameState = FIND;
          quaffle_start = millis();
          analogWrite(3, 0);   //Shut down motor
          digitalWrite(9, HIGH);   //Engage the Brake for Channel A
          break;
        } else {
          //forward @ full speed
           digitalWrite(12, HIGH); //Establishes forward direction of Channel A
           digitalWrite(9, LOW);   //Disengage the Brake for Channel A
           analogWrite(3, 255);   //Spins the motor on Channel A at full speed
           break;
        }
  }
}
