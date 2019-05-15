
#include "myHeader.h"
int counter;

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
  stopper.write(CLOSE);

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
  // Check to see if game is done, if so set gameState to DONE
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);

  curTime = millis() - start_time;
  if (curTime >= 300000) gameState = DONE;
  //If sopmething is infront of the robot, back-up and turn.Unless gameState is SHOOTING
  collisionCheck(red, green, blue);

  // Act depending on gameState
  switch (gameState) {

    case DONE:
      drive(90, 90);
      spinner.write(90);
      break;

    case START:
      // Get RGB values from color sensor
      delay(60);  // takes 50ms to read
      tcs.getRGB(&red, &green, &blue);

      // Rotate to the side then move forwards
      drive(90, 95); // turn left
      delay(2500);

      drive(100, 100); // go forward
      delay(2000);

      drive(95, 90); // turn back to the right
      delay(2700);

      drive(95, 95); // go straight


      // Check to see if there is red or blue
      while (returnColor(red, green, blue) != RED_COLOR &&  returnColor(red, green, blue) != BLUE_COLOR) {
        delay(60);  // takes 50ms to read
        tcs.getRGB(&red, &green, &blue);
      }
      startSide = returnColor(red, green, blue);
      // Serial.print("Start Side: ");
      // Serial.println(startSide);
      drive(90, 90);

      // If we find red or blue start searching for quaffles
      gameState = FIND;
      quaffle_start = millis();
      break;

    case FIND:
      quaffle_time = millis() - quaffle_start;

      // If time is up change to shooting mode
      if (quaffle_time > 180000) {
        gameState = FIND_GOAL;
        drive(90, 90);
      } else {
        quaffleSearch();
      }
      break;

    case FIND_GOAL:
      float red, green, blue;
      tcs.getRGB(&red, &green, &blue);
      drive(150, 150);
      if (returnColor(red, green, blue) == RED_COLOR || returnColor(red, green, blue) == BLUE_COLOR) {
        curSide = returnColor(red, green, blue);
        if (curSide == startSide) {
          while (analogRead(ir_sensor_center && pixy.getBlocks() > 0)) {
            int num_quafs = pixy.getBlocks();
            for (int i = 0; i < num_quafs; i++) {
              if (pixy.blocks[i].signature == YELLOW_COLOR) {
                if (pixy.blocks[i].y > 140) {
                  int x_coord = pixy.blocks[i].x;
                  if (pixy.blocks[i].x < 180) {
                    drive(140, 180);
                  } else if (pixy.blocks[i].x > 220) {
                    drive(180, 140);
                  } else drive(140, 140);
                }
              }
            }
          }
          drive(90, 90);
          gameState = SHOOTING;
          spinUp(200);
          delay(1000);
          stopper.write(OPEN);
          delay(1000);
          break;


        } else {
          drive(90, 160);
          delay(3000);
          while (analogRead(ir_sensor_center) < 400) {
            int num_quafs = pixy.getBlocks();
            for (int i = 0; i < num_quafs; i++) {
              if (pixy.blocks[i].signature == YELLOW_COLOR) {
                if (pixy.blocks[i].y > 90) {
                  int x_coord = pixy.blocks[i].x;
                  if (pixy.blocks[i].x < 180) {
                    drive(140, 180);
                  } else if (pixy.blocks[i].x > 220) {
                    drive(180, 140);
                  } else drive(140, 140);
                }
              }
            }
          }
          drive(90, 90);
          gameState = SHOOTING;
          spinUp(200);
          delay(1000);
          stopper.write(OPEN);
          delay(1000);
          break;
        }
      }
      break;

    case SHOOTING:
      drive(90, 90);
      shooting_time = millis() - shooting_start;
      while(shooting_time > 60000) {
        spinUp(255);
      }
      spinUp(0);
      break;
      }
  }
