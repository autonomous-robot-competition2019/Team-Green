This week we worked on code for reliably identifying the snitch and testing out ideas for our final robot.

To identify the snitch, we calibrated the PixyCam to reliably sense the orange of the snitch. The following code was used, which was simply a modified version of the code used to identify the goals.

```
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
```

This worked somewhat well, but it wasn't as reliable as we'd hoped. Next week, we will tweak the sensitivity of the PixyCam to iron out this issue.

Beyond this, Michael and Thomas worked more on theorycrafting for our robot. We came to the idea of using a motor to spin balls through a tube and into the goals. We will proceed with this idea, but it is unclear how we will capture and accumulate the quaffles. Travers and I worked on the code for the milestone.
