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
