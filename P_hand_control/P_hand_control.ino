#include <Servo.h>

#define MAX_SIZE 20
#define THRESHHOLD 1000
#define COUNTER_MAX 10
#define MAX_CLOSE 180
#define MAX_NO_STREAK 32000

Servo servo1;
//---------------- VARIABLES ------------------//
int input[MAX_SIZE] = {0};
int avgCounter = 0;
int muscleSig;
double signalAvg;
int toggle = 1;
int delayTime = 10; // ms
int next = 0;
int pin = 3;
int power = 0;
int val = 100;
int stopClose = 0;
int counter = 0;
int servoPin = 3;
int servo1Pos = 0;
int noStreak = 0;
int noStreakVal = 100;
int handOpenFlag = 2;
int relax = 1;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    servo1.attach(servoPin);
    servo1.write(0);   // set home position of the servo to zero
    delay(1000);
}

/************* FUNCTIONS ***************/
bool measure();
double avg();
void handMove();
void zeroSignals();


void loop() {
  
  muscleSig = analogRead(A5);

  if (muscleSig < THRESHHOLD){
    if (noStreak > MAX_NO_STREAK)
      noStreak = MAX_NO_STREAK;
    else
      noStreak++;
  }
  else
    noStreak = 0;

  Serial.print("no streak "); Serial.println(noStreak);

  // set up a rolling vector
  for(int i = 0; i < MAX_SIZE - 1; i++) {
    next = i+1;
    input[i] = input[next];
  }

  Serial.println(" ");

  input[MAX_SIZE-1] = muscleSig;
 
  signalAvg = avg();  // Average the vector at each point in time

  // if signals are as strong as a threshhold
  if(signalAvg > THRESHHOLD) {
    avgCounter++;
    if (handOpenFlag == 1 || handOpenFlag == 2)//&& relax)
      toggle = 1;
    else// if (relax)
      toggle = 0;
  }
    
  else {
    avgCounter = 0;
    
    // power not being zero indicates that the hand used to be closed to some degree.
    //if (power != 0)
    //toggle = !toggle; // next time there is a flex hand will be opened
    relax = 1;
    stopClose = 0;
    counter = 0;
  }

  Serial.print("hand open flag is "); Serial.println(handOpenFlag);
  // If user has flexed for long enough
  if ((avgCounter > COUNTER_MAX )) {//&& handOpenFlag == 0) || (avgCounter > COUNTER_MAX && handOpenFlag == 2) || ((avgCounter > COUNTER_MAX && handOpenFlag == 1 && noStreak > noStreakVal))) {
    
    //toggle = 1;
    relax = 0;
    // If they hand is not already closed close hand else open hand
    if(toggle){
        while(measure()) {
            counter++;
            handOpenFlag = 0;
    
              // if arm hasnt closed fully keep closing arm
            if(power < MAX_CLOSE)
                power += 2;
            else {
                power = MAX_CLOSE;
                stopClose++;
                Serial.println("STOP FLEXING");
            }
            // stop closing arm when arm has closed to the maximum capacity
            if(stopClose < 2) {
               Serial.print("power = ");
               Serial.println(power);
               servo1Pos = power;
               servo1.write(power);
            } 
            Serial.print("hand is moving hand" ); /* open flag is  "); Serial.println(handOpenFlag); */  
            delay(15);
        }
    }
    else {
      power = 0; 
      Serial.println("hand open");
      handOpen();
      handOpenFlag = 1;
    }
  }

  Serial.print(muscleSig);
  Serial.print("  ");
  Serial.println(signalAvg);
  delay(delayTime);
}

//average function

double avg() {
  int sum = 0;
  double average = 0;
  for(int i = 0; i < MAX_SIZE; i++) {
    sum = sum + input[i];
  }

  average = sum / MAX_SIZE;

  return average;
}

void zeroSignals() {
  for(int i = 0; i < MAX_SIZE; i++) {
    input[i] = 0;
  }
}

// function that enables the hand to open and close
void handOpen() {
  for (int pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    if(pos <= servo1Pos) {
      Serial.println("hand open");
      servo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(2);                       // waits 15ms for the servo to reach the position
      servo1Pos = pos;
      
    }
  }
  while(measure()) {
     delay(15);
  }
  
}

bool measure() {

  muscleSig = analogRead(A5);
  for(int i = 0; i < MAX_SIZE - 1; i++) {
        next = i+1;
        input[i] = input[next];
  }
  input[MAX_SIZE-1] = muscleSig;

  if (avg() > THRESHHOLD)
    return true;
  else
    return false;
  
}


