This past week we worked on finishing up the remainder of our milestones. We split into different teams to accomplish this. Travers  and Thomas worked on getting the robot to respond to information from the RGB sensor and the photoreceptor. 

Using the RGB Sensor, we were able to get the robot to respond differently upon encountering different colors on the mat. Upon encountering yellow, the robot would turn 180 degrees. When the robot encountered blue or red we had it continue forward but turn slightly to the right. 

Additionally we had the robot continue straight forward unless a bright light we shined a bright light on it (using the photoreceptor). The code for this can be found below.

````
const int left_motor = 3;
const int right_motor = 4;
const int photo_sensor = A1;

const int threshold = 300;


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(photo_sensor));
  if (analogRead(photo_sensor) < threshold){
    drive(130, 180);
  } else {
    drive(90, 90);
    delay(1000);
  }
}

void drive(int left, int right) {
  analogWrite(left_motor, left);
  analogWrite(right_motor, right);
}
````
Thomas also worked on figuring out what the shape and build of our final vehicle would be and how all of our sensors could be housed safely and compactly. He mocked up sketches and began to think about how the sketches could be translated into 3D-printable objects. 

Lastly John and Michael worked on getting the robot to respond to information from the PixyCam. The biggest struggle for the two of them was getting the sensor to correctly identify different colors reliably. They had to spend a lot of time tweaking thresholds and settings within the Pixy software to meet that end. As of the end of class they had written code to have the robot respond dynamically to different colors but did not get a chance to test it. 

THis coming week we hope to finish up the work we started last week and deal with the remainder of our milestones.
