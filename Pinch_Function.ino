
#include <Servo.h>

Servo thumbservo;  // create servo object to control a servo
Servo middleservo;
Servo ringservo;
// use variables instead of hard code

int pos = 0;    // variable to store the servo position
int thumbpos = 0;
int middlepos = 0;
int ringpos = 0;
int thumbMAXpinch = 180; //variable to store the max thumb position for pinch
int thumbMINpinch = 0;  //variable to store the min thumb position for pinch
int middleMAXpinch = 180;
int middleMINpinch = 0;
int ringMAXpinch = 0;

void setup() {
  thumbservo.attach(9);  // attaches the servo on pin 9 to the servo object
  middleservo.attach(10);
  ringservo.attach(11);
  thumbservo.write(0);
  middleservo.write(0);
  ringservo.write(0);
}
void pinch() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree

    if (pos < thumbMAXpinch && thumbpos <= pos) {
      thumbpos = pos;
                 thumbservo.write(thumbpos);     //thumbservo moves to 180 degrees
    }
    if (pos < middleMAXpinch) {
      middlepos = pos;
                  middleservo.write(middlepos);  //middleservo moves to 180 degrees
    }
    if (pos > ringMAXpinch) {
      ringservo.write(ringpos);       //ring servo moves to 0 degrees
    }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void loop() {
  pinch();
}

