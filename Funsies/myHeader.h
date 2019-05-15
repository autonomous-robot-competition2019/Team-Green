#include <SPI.h>
#include <Pixy.h> 
#include <Servo.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// CONSTANTS
// =========


// Servos
const int left_motor = 4;
const int right_motor = 5;
const int spin = 6; 
const int my_stop = 7;

const int GREEN_COLOR = 3; // green
const int ORANGE_COLOR = 5; // orange
const int RED_COLOR = 6;
const int BLUE_COLOR = 7;
const int YELLOW_COLOR = 8;

// IR
const int ir_sensor_center = A8;
const int ir_sensor_left = A9;
const int ir_sensor_right = A10;
const int threshold = 530;//Need to adjust this 

// State Logic, m=mode
const int START = 1; 
const int FIND = 2;
const int FIND_GOAL = 3;
const int SHOOTING = 4; 
const int DONE = 0;


// Side
const int RED_SIDE = 0;
const int BLUE_SIDE = 1; 

// Directions
const int NONE = 0;
const int LEFT = 1;
const int CENTER = 2;
const int RIGHT = 3;
const int FRONT = 4;

// our RGB -> eye-recognized gamma color

byte gammatable[256];

void setGamma() {
for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;

    gammatable[i] = 255 - x;
    //Serial.println(gammatable[i]);
  }
}




// Variables
int startSide;
int gameState; 
int curSide;
int target_color = 3;
int pos = 0;    // variable to store the servo position
int previousState;
unsigned long curTime;
unsigned long start_time;
unsigned long quaffle_start;
unsigned long quaffle_time;
unsigned long shooting_start;
unsigned long shooting_time;

// Objects 
// =======
Pixy pixy;
Servo leftWheel;
Servo rightWheel;
Servo spinner;
Servo stopper;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

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
    			//Serial.println(minY);
    			if (pixy.blocks[i].x < 125) direction = LEFT;
    			else if (pixy.blocks[i].y > 145)  direction = RIGHT;
    			else if (pixy.blocks[i].y < 25) direction = FRONT;
    			else direction = CENTER;
    		}    
    	} 

  	}
  	Serial.println(direction);
  	return direction;
}

void quaffleSearch(int direction) {
	switch(direction) {

		case NONE:
			drive(90,100);
			break;

		case LEFT:
			drive(90,100);
			break;

		case RIGHT:
			drive(100,90);
			break;

		case CENTER:
			drive (140,140);
			delay(1500);
			break;
		case FRONT:
			drive(120,120);
			break;
	}
}
int returnColor(float red,float green, float blue)
{
	if (red > 150 && green < 60 && blue < 60) return RED_COLOR;
	else if (red < 50 && green > 75 && blue > 100) return BLUE_COLOR;
	else if (red > 80 && green > 90 && blue < 50) return YELLOW_COLOR;
	else return 0;
}

int isRedOrBlue() {
	int direction = NONE;
	int num_quafs = pixy.getBlocks();
	for (int i = 0; i < num_quafs; i++) {
    	if (pixy.blocks[i].signature == RED_COLOR || pixy.blocks[i].signature == BLUE_COLOR){
			if (pixy.blocks[i].x < 125) direction = LEFT;
    		else if (pixy.blocks[i].y > 145)  direction = RIGHT;
    		else if (pixy.blocks[i].y < 25) direction = FRONT;
    		else direction = CENTER;  		   
    	} 

  	}
  	return direction;
}

void middleSearch(int direction) {
	switch(direction) {

		case NONE:
			drive(90,100);
			break;

		case LEFT:
			drive(90,100);
			break;

		case RIGHT:
			drive(100,90);
			break;

		case CENTER:
			drive (140,140);
			delay(1500);
			break;

		case FRONT:
			drive(120,120);
			break;
	}
}
