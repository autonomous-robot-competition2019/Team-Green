#include <SPI.h>
#include <Pixy.h> 
#include <Servo.h>

// CONSTANTS
// =========

// Servos
const int left_motor = 4;
const int right_motor = 5;
const int spin = 6; 
const int stop = 7;

const int GREEN_COLOR = 3; // green
const int ORANGE_COLOR = 5; // orange
const int left = 0;
const int right = 180;

// IR
const int ir_sensor = A1;
const int threshold = 300;

// State Logic
const int mSearch = 0; 
const int mFindGoal = 1;
const int mShooting = 2; 
const int mFindSide = 4;
const int mAvoidColl = 5;


// Side
const int RED_SIDE = 0;
const int BLUE_SIDE = 1; 

// Directions
const int NONE = 0;
const int LEFT = 1;
const int CENTER = 2;
const int RIGHT = 3;


// Variables
int gameState; 
int curSide;
int target_color;
int isShooting = 0;
unsigned long start;

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

// return 0 -no quaffle, 1 - closest to left, 2 - closest ahead, 3 - closest to right
int findClosestQuaffle() {
	int minY = 1000;
	int direction = NONE;
	int num_quafs = pixy.getBlocks();
  	for (int i = 0; i < num_quafs; i++) {
    	if (pixy.blocks[i].signature == target_color){
    		if (pixy.blocks[i].y < minY) {
    			minY = pixy.blocks[i].y;
    			if (pixy.blocks[i].x < 152) direction = LEFT;
    			else if (pixy.blocks[i].y > 168)  direction = RIGHT;
    			else direction = CENTER;
    		}    
    	} 

  	}

  	return direction;
}

void quaffleSearch(int direction) {
	switch(direction) {

		case NONE:
			drive(90,95);
			break;

		case LEFT:
			drive(90,95);
			break;

		case RIGHT:
			drive(95,90);
			break;

		case CENTER:
			drive (100,100);
			break;
	}
} 
