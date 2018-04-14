#define MAX_SIZE 20
#define THRESHHOLD 1000
#define COUNTER_MAX 40
#define MAX_CLOSE 180

//---------------- VARIABLES ------------------//
int input[MAX_SIZE] = {0};
int avgCounter = 0;
int muscleSig;
double signalAvg;
int toggle = 1;
int delayTime = 20; // ms
int next = 0;
int pin = 3;
int power = 0;
int val = 100;
int stopClose = 0;
int mult = 1;
int counter = 0;


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}


/************* FUNCTIONS ***************/
double avg();
void handMove();


void loop() {
  
  muscleSig = analogRead(A5);

  // set up a rolling vector
  for(int i = 0; i < MAX_SIZE - 1; i++) {
    next = i+1;
    input[i] = input[next];
  }
//
//  for (int i = 0; i < MAX_SIZE - 1; i++) {
//    Serial.println(input[i]);
//    delay(200);
//  }

  Serial.println(" ");

  input[MAX_SIZE-1] = muscleSig;
 
  signalAvg = avg();  // Average the vector at each point in time

  // if signals are as strong as a threshhold
  if(signalAvg > THRESHHOLD)
    avgCounter++;
  else {
    avgCounter = 0;
    // power not being zero indicates that the hand used to be closed to some degree.
    if (power != 0)
      toggle = !toggle; // next time there is a flex hand will be opened
    power = 0; 
    stopClose = 0;
    counter = 0;
  }

  // If user has flexed for long enough
  if (avgCounter > COUNTER_MAX) {
    mult = mult*2;

    // If they hand is not already closing close hand else open hand
    if(toggle){
        counter++;

        // close hand more if still flexing for a time gap of 5
        if(counter == 5) {
          // if arm hasnt closed fully keep closing arm
          if(power < MAX_CLOSE)
            power += 5;
          counter = 0;
        }

        //Making sure the angle given to the hand isnt too high
        if (power > MAX_CLOSE) {
          power = MAX_CLOSE;
          stopClose++;
          Serial.println("STOP FLEXING");
        }

        // stop closing arm when arm has closed to the maximum capacity
        if(stopClose < 2) {
           analogWrite(pin,power);
        }    
    }
    else {
      Serial.println("hand open");
      handOpen();
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

// function that enables the hand to open and close
void handOpen() {
    digitalWrite(pin,LOW);
}

