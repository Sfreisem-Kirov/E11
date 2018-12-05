#include <Servo.h>
#define SERVOPIN 10


void testServo(){
  initServo();
  servo.write(90); delay(2000);
}
void initServo(){
  pinMode(SERVOPIN, OUTPUT);
  servo.attach(SERVOPIN);
}
