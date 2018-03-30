#include <Servo.h>

Servo thumbservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo middleservo;
Servo ringservo;
 // use variable not numbers

int pos = 0; // variable to store the servo position
int thumbPos = 0; // variable to store the thumb servo position
int middlePos = 0; // variable to store the middle servo position
int ringPos = 0; // variable to store the ring servo position

int thumbMAXmouse = 20; // variable to store the MAX thumb servo position
int middleMAXmouse = 80; // variable to store the MAX middle servo position
int ringMAXmouse = 50; // variable to store the MAX ring servo position

void setup() {
  thumbservo.attach(9);  // attaches the servo on pin 9 to the servo object
  middleservo.attach(10);  // attaches the servo on pin 10 to the servo object
  ringyservo.attach(11);  // attaches the servo on pin 11 to the servo object
   
   thumbservo.write(0);  
   middleservo.write(0);  
   ringservo.write(0);  
  
}
void mouseTap(){
  for (pos = 0; pos <= 180; pos += 7) { // goes from 0 degrees to 180 degrees
    // in steps of 7 degree
    if ( pos < thumbMAXmouse && pos >= thumbPos) { // we want the thumb position to go to thumb max
      thumbPos = pos;
      thumbServo.write(thumbPos);
    }

    if ( pos < middleMAXmouse && pos >= middlePos) { // we want the middle position to go to middle max
      middlePos = pos;
      middleServo.write(middlePos);
    }

    if ( pos < ringMAXmouse && pos >= ringPos) {
      ringservo.write(ringPos); // we want the ring position to go to ring max
    }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  }
  // Next Steps: we need to open the mouse tap
  for (pos = 180; pos >= 0; pos -= 12) { // goes from 180 degrees to 0 degrees
 
 if ( pos < middleMAXmouse && pos >= middlePos) { // we want the middle position to go to middle max
      middlePos = pos;
      middleServo.write(middlePos);
    }
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
void loop() {
  mouseTap();
}
