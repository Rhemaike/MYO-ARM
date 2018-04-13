
//length requirements for pulses
float     pe = 400;        //pulse excitation required for trigger
float     spb=10;         //short pulse lower time boundary
float     lpb=40;          //long pulse time boundary
float     dcat=40;         //down count activation time. down time required to activate movement minus time for ra to settle below pe

int     di;             //direct input
int     c1=5;           //counter 1
int     plc=0;          //Pulse Length Counter
int     spc=0;          //Pulse counter
int     dc=0;           //down count
int     dia[10];        //direct input array
int     ra;            //rolling average 
int     ps;            //Pulse Strength
int     ms=1;            //Mode Select 
int     bp=false;       //Base Position

  //assiging LEDs to simulate arm movements!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
float   led1=2;
float   led2=3;
float   led3=4;
float   led4=5;
int     LED1=LOW;
int     LED2=LOW;
int     LED3=LOW;
int     LED4=LOW;
 
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  //assiging LEDs to simulate arm movements!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

}


void loop() 
{
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

  //setting ra (rolling average array) to the average of the last 5 di(direct input)
  ra= (dia[c1]+dia[c1-1]+dia[c1-2]+dia[c1-3]+dia[c1-4])/5;         //I think ra will work as not an array

      ps=ra/100;

  if (ra>=pe)         //if pulse excited, count how long it stays excited for and scale direct input (di) to pulse strength (ps) to use as servo unit step
    {
      plc=plc+1;
      dc=0; 

    }
  else 
    {
      dc=dc+1;
      plc=0;
    }


  if (plc==spb)                   //Whenever pulse length counter passes short pulse boundary
  {
    spc=spc+1;                    //Incriment Short Pulse Count
  }
  if (dc>=dcat)                   //activation of short pulse command
  {
    if (bp == true)               //do this when hand is in Base Position
    {  
        if (spc==1)               //one pulse, base position action
          {
            Serial.print("<LEFTCLICK>");
          }
        if (spc==2)
          {
            ms=2;                  //mode is now 2
            Serial.print("<RIGHTMOUSECLICK>");            //<RIGHTMOUSECLICK>
          }
        if (spc==3)
          {
            ms=3;                  //mode is now 3
            Serial.print("<DOUBLECLICK>");            //<DOUBLECLICK>
          }  
        spc=0;
    }
    else                            //When arm not in Base Position do this
    {  
            if (spc==1)               //one pulse, base position action
          {
            ms=1;                 //set mode to 1
            Serial.print("<BASEPOSITION>");
            bp=true;              //indicating hand in Base Position
          }
        if (spc==2)
          {
            ms=2;                  //mode is now 2
            bp=false;              //your hand is no longer in the upright and Base Position
            Serial.print("<POINTERPOSITION>");
          }
        if (spc==3)
          {
            ms=3;                  //mode is now 3
            bp=false;              //your hand is no longer in the upright and Base Position
            Serial.print("<DOSOMESHIT>");
            
          }
   }
   spc=0;
  }

  if (plc>=lpb)                 //Do this when Pulse Length Counter is greater than Long Pulse Boundary
    {
      spc=0;
      
      if (ms==1)
        {
            Serial.print("<POWERGRIP>");    // with Pulse Strength (ps) as the speed control
            bp=false;              //your hand is no longer in the upright and Base Position
        }
      if (ms==2)
        {
            Serial.print("<PINCHRINGRCLOSED>"); //with Pulse Strength (ps) as the speed control
             bp=false;              //your hand is no longer in the upright and Base Position
        }
      if (ms==3)
        {
            Serial.print("<PINCHRINGROPEN>");  //with Pulse Strength (ps) as the speed control
             bp=false;              //your hand is no longer in the upright and Base Position
        }
    }
  digitalWrite(led1,LED1);
  digitalWrite(led2,LED2);
  digitalWrite(led3,LED3);
  digitalWrite(led4,LED4);

    // print values to serial monitor
  Serial.print("ra=");
  Serial.print(ra);
  Serial.print(',');
  Serial.print("plc=");
  Serial.print(plc);
  Serial.print(',');
  Serial.print("dc=");
  Serial.print(dc);
  Serial.print(',');
  Serial.print("ms=");
  Serial.print(ms);
  Serial.print(',');
  Serial.print("spc=");
  Serial.print(spc);
  Serial.print(',');
  Serial.print("bp=");
  Serial.print(bp);
  Serial.print(',');
  Serial.print("ps=");
  Serial.print(ps);
  Serial.println(',');

  delay(1);        // delay in between reads for stability
}
