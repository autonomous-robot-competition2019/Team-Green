
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
  drive(180, 180);
  delay(4000);
  drive(90, 90);
  

}

void loop() {
  counter++;
  spinUp(255);
  if (counter > 1000) {
    stopper.write(OPEN);
  }

}
