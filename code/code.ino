 #include <Servo.h>

const int numJoints = 8;
Servo joints[8];
int potPrev[8];
int jointMap[8] = {1, 0, 7, 6, 5, 4, 3, 2};

int val;    // variable to read the value from the analog pin

void setup() {
  for (int i = 0; i < numJoints; i++) {
    joints[i].attach(i + 2);
    potPrev[i] = 0;
  }
  Serial.begin(9600);
  Serial.println("Begin");
}

void loop() {
  for (int i = 0; i < numJoints; i++) {
    mapPotToJoint(i);
  }
  Serial.println(" ");
  delay(50);                          // waits for the servo to get there
}

void mapPotToJoint(int id) {
  potPrev[id] = 0;
  val = (analogRead(jointMap[id]) + potPrev[id]) / 2;   // reads the value of the potentiometer (value between 0 and 1023)

  Serial.print(val); 
  Serial.print(" ");

  if((val - 5) >= potPrev[id] || (val + 5) <= potPrev[id]) {
    potPrev[id] = val;
    val = map(val, 0, 460, 180, 0); 
    // scale it to use it with the servo (value between 0 and 180)
    val = constrain(val, 1, 179);
    joints[id].write(val);
  } else {
    potPrev[id] = val;
  }
}

