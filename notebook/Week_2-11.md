This week we focused on testing the hardware that is available to us this semester. We began by hooking up the PixyCam and testing its color detection capabilities. We calibrated the PixyCam to detect Red, Blue, and Yellow, and adjusted the respective sensitivities for the light levels in the room to ensure a tight, accurate range of color detection. 

Once we got that working, we decided to begin testing other sensors to learn how we can integrate information from those sensors in the future to get our robot to do something useful. We did a test where we would light up a color LED if and only if the IR sensor values were above a certain threshold. 
~~~~
led_pin = 7;
ir_sensor = A11;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (analogRead(ir_sensor) > 300){
     digitalWrite(led_pin, HIGH);
  }
}
~~~~
We edited the native "Blink" example code to achieve this.

After this, we tested a positional actuator to get into the motions of using these actuators, as they will likely be useful in the near future. The code for this was lost, but it is a simple loop in which the motor switches between position 45 and 100 in 1 second intervals.

After this, we decided that in order to make progress on the milestones, we needed a chassis. After a quick discussion, we decided on using LEGOs to make a quick chassis that is modular yet robust. Pictures below: (Pictures to come after we go into class again).

(FRONT VIEW)

(SIDE VIEW)

(BACK VIEW)

With this chassis, we plan to get the first three milestones done on 2-18-2019.
