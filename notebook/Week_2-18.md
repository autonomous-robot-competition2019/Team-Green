This week, we planned to get the first three milestones completed.  To that end, we modified our chassis from last week to be able to fit a battery pack with a reasonable weight distribution along with building a scaffold on the front to append an IR sensor. 

To complete the first three milestones, it was enough to complete milestone 3. To that end, we wrote code that would enable our robot turn away from obstacles, while driving forward otherwise. The code for this behavior is included below

~~~~
const int left_motor = 3;
const int right_motor = 4;
const int ir_sensor = A1;

const int threshold = 300;


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(ir_sensor));
  if (analogRead(ir_sensor) < threshold){
    drive(130, 180);
  } else {
    drive(70, 20);
    delay(1000);
  }
}

void drive(int left, int right) {
  analogWrite(left_motor, left);
  analogWrite(right_motor, right);
}
~~~~

This code did the trick. We created a variable that represented our IR sensor's threshold, i.e., the value that, if the IR signal exceeded, would prompt our robot to turn away. Anything above this value would indicate that there was an obstacle present, and anything below would indicate that the robot can continue along merrily. 

With that, we completed milestones 1, 2, and 3.

Pictures to come.

Acknowledgements: Travers was out sick, and presumably did not infect us with his prediagnosed bronchitis. John and Thomas worked on getting the code right, John crimped some wires to get the IR sensor working. Michael and Thomas made sure our robot's chassis could house the necessary hardware, while simultaneously increasing the aesthetic appeal of the robot.
