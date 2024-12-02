#include <AFMotor.h>
#include <NewPing.h>
#define ECHO_PIN A0
#define TRIGGER_PIN A1
#define MAX_DISTANCE 100

AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
bool start = true;
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);

void setup()
{
  Serial.begin(9600);
	//Set initial speed of the motor & stop
	setAllSpeed(190);
}

void loop() 
{
  if (start){
    delay(6000);
  }
  delay(300);
  int iterations = 1;
  float duration = sonar.ping_median(iterations);
  float distance = (duration / 2 ) * 0.0343;
  Serial.println("START MOVEIT MOVEIT");
  Serial.println(distance);
  if (distance >= 25 || distance == 0 ){
    Serial.println("moving forward");
    moveForward();
  } else{
    Serial.println("checking left");
    checkLeft();
  }
  start = false;
}

void setAllSpeed(int speed){
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
}

void moveForward(){
  motor2.run(FORWARD);
  motor3.run(FORWARD);
}
void checkLeft(){
  moveBackward();
  delay(100);
  moveLeft();
  delay(100);
}
void moveBackward(){
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
}

void motorStop(){
  motor2.run(RELEASE);
  motor3.run(RELEASE);
}

void moveLeft(){
  motor3.run(BACKWARD);
  motor2.run(FORWARD);
}

void moveRight(){
  motor3.run(FORWARD);
  motor2.run(BACKWARD);
}

// int readPingFRONT() { 
//   digitalWrite(trigPin1, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin1, HIGH);    // Give a pulse of 10 microseconds on TRIG
//   delayMicroseconds(10);
//   digitalWrite(trigPin1, LOW);
//   long duration = pulseIn(echoPin1, HIGH);  // Check the time elapsed in receiving back the pulse on ECHO
//   int distanceCm = duration * 0.034 / 2;  // Convert to distance in centimeters

//   return distanceCm;
// }

// // int readPingBACK() { 
// //   digitalWrite(trigPin2, LOW);
// //   delayMicroseconds(2);
// //   digitalWrite(trigPin2, HIGH);    // Give a pulse of 10 microseconds on TRIG
// //   delayMicroseconds(10);
// //   digitalWrite(trigPin2, LOW);
// //   long duration = pulseIn(echoPin2, HIGH);  // Check the time elapsed in receiving back the pulse on ECHO
// //   int distanceCm = duration * 0.034 / 2;  // Convert to distance in centimeters

// //   return distanceCm;
// // }

// void mode1(){
//   moveRight();
//   moveLeft();
// }



