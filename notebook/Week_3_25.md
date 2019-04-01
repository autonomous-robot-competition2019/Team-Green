ournal 3-25

This week, we attempted to complete the milestone in which we must reliably identify goals. To do this, we used the PixyCam to find yellow color signatures. These would correspond to either the yellow taped boundaries or the goals  (in an ideal world). To avoid going towards tape, we adjusted the thresholds of the yellow color range such that, the majority of the time, the only signatures in view were the goals.

Next, we wrote the following code:
```
void loop() {
 int num_quafs = pixy.getBlocks();
 for (int i =0; i < num_quafs; i++) {
   if (pixy.blocks[i].signature == target_color) {
     if(pixy.blocks[i].height > 50 &&  pixy.blocks[i].width > 75 && pixy.blocks[i].x > 130 && pixy.blocks[i].x <= 160) {
       while (analogRead(ir_sensor) < threshold){
         drive(straight,straight);
       }
       drive(90,90);
       delay(2000);
     } else {
       drive(90,100);
       }
   }
 }
}
``

What is going on here is that if our robot sees a yellow color signature that is sufficiently large, it will go towards it in a straight line. Otherwise it would spin until it has located such a signature. This helps us avoid going towards the boundaries (false positive) and instead go towards the goals (true positive). While this code was somewhat consistent, we decided that it was not consistent enough to warrant the completion of the milestone.

To that end, we will adjust the logic that checks the proportions of the yellow color signatures so that it correctly identifies goals more often.

Travers and John worked on the code for this week. Michael and Thomas were still returning from their spring breaks and were unable to make it to lab.
