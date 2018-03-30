
//length requirements for pulses
float     pe = 500;        //pulse excitation required for trigger
float     splb=10;         //short pulse lower time boundary
float     lpb=40;          //long pulse time boundary
float     dcat=40;         //down count activation time. down time required to activate movement minus time for raa to settle below pe

int     di;             //direct input
int     c1=5;           //counter 1
int     c3=0;
int     pc=0;           //Pulse counter
int     dc=0;           //down count
int     dia[10];        //direct input array
int     raa;            //rolling average array 

  //assiging LEDs to simulate arm movements!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
float   led1=2;
float   led2=3;
float   led3=4;
float   led4=5;
int     LED1=LOW;
int     LED2=LOW;
int     LED3=LOW;
int     LED4=LOW;

void  pinch() {
  
  
  
}

void  mouseTab() {
  
  
  
}
 
void  powerGrip() {
  
  
  
}
 
 
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //assiging LEDs to simulate arm movements!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

}


void loop() {
  //setting di to equal direct input
  di = analogRead(A5); 
  dia[c1]=di;
  
  c1=c1+1;            //incrimenting the counter "c1"
  if (c1>=10)         //setting a rolling direct input array
  {
    c1=5;
    dia[0]= dia[5];
    dia[1]= dia[6];
    dia[2]= dia[7];
    dia[3]= dia[8];
    dia[4]= dia[9];
  }

  //setting raa (rolling average array) to the average of the last 5 di(direct input)
  raa= (dia[c1]+dia[c1-1]+dia[c1-2]+dia[c1-3]+dia[c1-4])/5;         //I think raa will work as not an array

   //set up short pulse (sp)
  if (raa >= pe)
  {
   c3=c3+1; 
   dc=0;
  }
  else
  {
    c3=0;
  }
  if (c3==splb)
  {
    pc=pc+1;
  }
  if (raa < pe)
  {
    dc=dc+1;
  }
  if (dc==dcat)
  {      
    if (pc==1)      //action 1 sequence
      {
         LED1=HIGH;
         LED2=LOW;
         LED3=LOW;
         LED4=LOW;      
      }
    if  (pc==2)
       {
   
         LED1=LOW;
         LED2=HIGH;
         LED3=LOW;
         LED4=LOW;
       }
    pc=0;
  }
      if  (pc==3)
      {
         LED1=LOW;
         LED2=LOW;
         LED3=HIGH;
         LED4=LOW;    
      }
//Long pulse bitches!!! Reset erthing
  if (c3>=lpb)
  {
   LED1=LOW;    //all LEDs off sept reset LED
   LED2=LOW;
   LED3=LOW;
   LED4=HIGH;
   pc=0;
  }

  digitalWrite(led1,LED1);
  digitalWrite(led2,LED2);
  digitalWrite(led3,LED3);
  digitalWrite(led4,LED4);

    // print values you to serial monitor
  Serial.print("pc=");
  Serial.print(pc);
  Serial.print(',');
  Serial.print("c3=");
  Serial.print(c3);
  Serial.print(',');
  Serial.print("di=");
  Serial.print(di);
  Serial.print(',');
  Serial.print("raa=");
  Serial.print(raa);
  Serial.println(',');

  delay(1);        // delay in between reads for stability
  
  //testing git hub 123
  //testing git hub 123
}
