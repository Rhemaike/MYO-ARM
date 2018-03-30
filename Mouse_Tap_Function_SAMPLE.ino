#include <Servo.h>

Servo thumbservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo middleservo;
Servo ringservo;
 // use variable not numbers

int pos = 0;    // variable to store the servo position
int thumbPos = 0;
int middlePos = 0;
int ringPos = 0;

void setup() {
  thumbservo.attach(9);  // attaches the servo on pin 9 to the servo object
  middleservo.attach(10);  // attaches the servo on pin 10 to the servo object
  ringyservo.attach(11);  // attaches the servo on pin 11 to the servo object
   
   thumbservo.write(0);  
   middleservo.write(0);  
   ringservo.write(0);  
  
}
void mouseTap(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    if ( pos < 170 && thumbPos <= pos) { // we want the thumb position to go to 60 degrees
      thumbPos = pos;
      thumbServo.write(thumbPos);
    }

    if ( pos < 120) { // we want the middle position to go to 120 degrees
      middlePos = pos;
      middleServo.write(middlePos);
    }

    if (ringPos <= pos) {
      ringservo.write(ringPos); // we want the ring position to go to 180 degrees
    }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void loop() {
  mouseTap();
}
