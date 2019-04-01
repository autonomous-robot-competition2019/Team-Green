This week we worked on completing our checkpoints before break. During class we were able to get our bot to respond to input from the IR sensor, the Pixy Cam, the RGB sensor, and the light sensor. 

For the IR sensor we had the robot turn around when encountering an object close in front of it. For the Pixy Cam and RGB sensors we had the robot react differently according to the color that it saw. For example if the robot saw enough yellow it would turn around. 

# RGB Test
```
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Servo.h>

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define red_pin 6
#define green_pin 5
#define blue_pin 7
const int left_motor = 3;
const int right_motor = 4;
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];

Servo leftWheel, rightWheel;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  //Serial.println("Color View Test!");

  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  leftWheel.attach(3);
  rightWheel.attach(4);

}

// The commented out code in loop is example of getRawData with clear value.
// Processing example colorview.pde can work with this kind of data too, but It requires manual conversion to 
// [0-255] RGB value. You can still uncomments parts of colorview.pde and play with clear value.
void loop() {
  float red, green, blue;
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));

//  Serial.print("\t");
//  Serial.print((int)red, HEX); Serial.print((int)green, HEX); Serial.print((int)blue, HEX);
  Serial.print("\n");
  if (green > 80 & red > 100) 
  {drive(10,90); 
  delay(3000);}
  else if (red > 140) {drive(110,140);}
  else if (blue > 100) {drive(90,90);}
  else { drive(80,80);
  }
  }

  void drive(int left, int right) {
  leftWheel.write(left);
  rightWheel.write(180 - right);
}
  
//  uint16_t red, green, blue, clear;
//  
//  tcs.setInterrupt(false);  // turn on LED
//
//  delay(60);  // takes 50ms to read
//
//  tcs.getRawData(&red, &green, &blue, &clear);
//  
//  tcs.setInterrupt(true);  // turn off LED
//
//  Serial.print("C:\t"); Serial.print(int(clear)); 
//  Serial.print("R:\t"); Serial.print(int(red)); 
//  Serial.print("\tG:\t"); Serial.print(int(green)); 
//  Serial.print("\tB:\t"); Serial.print(int(blue));
//  Serial.println();

 

int led_activate(int pin){
  if (pin == green_pin){
    pinMode(blue_pin, INPUT);
    pinMode(red_pin, INPUT);
    pinMode(green_pin, OUTPUT);
  } else if (pin == blue_pin){
    pinMode(red_pin, INPUT);
    pinMode(green_pin, INPUT);
    pinMode(blue_pin, OUTPUT);
  } else {
    pinMode(red_pin, OUTPUT);
    pinMode(blue_pin, INPUT);
    pinMode(green_pin, INPUT);
  }
  return 0;
}
```

# Pixy Cam
```
#include <SPI.h>
#include <Pixy.h> 
#include <Servo.h>

const int left_motor = 3;
const int right_motor = 4;
const int target_color = 4;
const int left = 0;
const int right = 180;
const int straight = 100;
const int ir_sensor = A1;
const int threshold = 300;
Pixy pixy;
Servo leftWheel;
Servo rightWheel;
void setup(){
  Serial.begin(9600);
  pixy.init();
  leftWheel.attach(3);
  rightWheel.attach(4);
}
void loop() {
      if (analogRead(ir_sensor) > threshold){
    drive(90, 90);}
  else find_quaffle();

}
void find_quaffle() {
  int num_quafs = pixy.getBlocks();
  for (int i = 0; i < num_quafs; i++) {
    if (pixy.blocks[i].signature == target_color){
      if (pixy.blocks[i].x < 130) {
        drive(140,100);
      } else if (pixy.blocks[i].x >= 160){
        drive(100, 140);
      } else {
        drive(straight, straight);
      }
    }
    else drive(90,90);
  }
}


  void drive(int left, int right) {
  leftWheel.write(180 - left);
  rightWheel.write(right);
}
```
# Light Sensor
