#include <SPI.h>
#include <Pixy.h> 
#include <Servo.h>

// CONSTANTS
// =========

// Servos
extern const int left_motor = 4;
extern const int right_motor = 5;
extern const int spin = 6; 
extern const int stop = 7;

extern const int target_color = 3; // green
extern const int left = 0;
extern const int right = 180;

// IR
extern const int ir_sensor = A1;
extern const int threshold = 300;

// Objects 
// =======
Pixy pixy;
Servo leftWheel;
Servo rightWheel;
Servo spinner;
Servo stopper;

void drive(int left, int right) {
  leftWheel.write(left);
  rightWheel.write(180 - right);
}

void spinUp(int speed) {
  digitalWrite(12,HIGH);
  digitalWrite(9,LOW);
  analogWrite(3,speed);		
}
