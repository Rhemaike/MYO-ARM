#define MAX_SIZE 20
#define THRESHHOLD 1000
#define COUNTER_MAX 40

int input[MAX_SIZE] = {0};
int avgCounter = 0;
int muscleSig;
double signalAvg;
int toggle = 1;
int delayTime = 20; // ms
int next = 0;
int pin = 3;
int tracker = 1;
int val = 100;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
}

/************* FUNCTIONS ***************/
double avg();
void handMove(int toggle);



void loop() {
  
  muscleSig = analogRead(A5);

  // set up a rolling vector

  for(int i = 0; i < MAX_SIZE - 1; i++) {
    next = i+1;
    input[i] = input[next];
  }

  Serial.println("ARRAY");
//
//  for (int i = 0; i < MAX_SIZE - 1; i++) {
//    Serial.println(input[i]);
//    delay(200);
//  }

  Serial.println(" ");

  input[MAX_SIZE-1] = muscleSig;
 
  signalAvg = avg();  // Average the vector at each point in time

  if(signalAvg > THRESHHOLD)
    avgCounter++;
  else
    avgCounter = 0;

  if (avgCounter == COUNTER_MAX) {
    Serial.println("long Flex");
    handMove(toggle);
    toggle = !toggle;
    tracker++;
  }
  else if (avgCounter > COUNTER_MAX+val){
    Serial.println("STOP FLEXING");
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
void handMove(int toggle) {
  if (toggle)
    digitalWrite(pin,HIGH);
  else
    digitalWrite(pin,LOW);
}

