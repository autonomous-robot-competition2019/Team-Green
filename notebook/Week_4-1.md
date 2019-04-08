This week, we began by focusing on correctly and reliably identifying the yellow goals (milestone 7). To do so, we wrote the following code:

'''
void loop() {
  if (analogRead(ir_sensor) > threshold) {
    drive(90, 90);
    delay(1000);
    drive(90, 100);
  } else {
    find_goal();
  }
}


void find_goal() {
  int num_quafs = pixy.getBlocks();
  for (int i = 0; i < num_quafs; i++) {
    if (pixy.blocks[i].signature == target_color) {
      if (pixy.blocks[i].x < 130) {
        drive(110, 180);
        //delay(100);
      } else if (pixy.blocks[i].x > 160) {
        drive(180, 110);
        //delay(100);
      } else if (pixy.blocks[i].x <= 150 && pixy.blocks[i].x >= 140) {
        drive(straight, straight);
        //delay(100);
      } else {
        drive(90, 100);
      }
    } else {
      drive(90,100);
    }
  }
}

void drive(int left, int right) {
  leftWheel.write(180 - left);
  rightWheel.write(right);
}
'''

The robot begins by determining if there is something directly in front of it. If so, it will stop, wait for one second, then back up while turning slightly. This was done to prevent the robot from getting stuck. If there is nothing in its way, then it will perform a seeking operation, "find_goal()". This function searches through the array of objects that the PixyCam sees. If an object in this array corresponds to the target color (yellow), then the remaining logic determines where in the PixyCam's field of vision the object is. If it is to the left, then the robot will go to the left. If it is to the right, then the robot will go to the right. Otherwise, if it is directly ahead, our robot will go forward. This loop continues until either the robot is directly in front of the object, in which case it will return to the default loop condition of stopping, waiting for one second, and then backing up, or the loop will continue until the robot no longer sees the object, in which case it will slowly turn to the left, awaiting a new target.

Beyond this, we also began sketching quick mockups of and discussing ideas for our final robot's chassis. We have a few ideas, but they all revolve around the quaffle collection mechanism. One idea for this mechanism is to have sort of a bucket (like a bulldozer), with a channel attached to the back that collects the quaffles into a storage unit, which it will dump into one of the goals. Some other zany, but fun, ideas include miniature vacuum cleaners, simple conveyor belt/relay systems, and more. We will narrow these ideas down on 4/8.

Travers and John worked on the code for milestone 7. Michael and Thomas generated ideas for the robot chassis and made some mockups (3D and hand-drawn).
