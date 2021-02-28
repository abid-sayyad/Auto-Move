 #define Q0 10                                                                       //take input from HT12D, connect pin D10 
#define Q1 11                                                                       //take input from HT12D, connect pin D11  
#define Q2 12                                                                       //take input from HT12D, connect pin D12
#define Q3 13                                                                       //take input from HT12D, connect pin D13

#define TRIGGER_PIN_RIGHT 6                                                         //Connect Trig pin to D4
#define ECHO_PIN_RIGHT 7                                                            //Connect Echo pin to D5 


#define TRIGGER_PIN_LEFT 8                                                          //Connect Trig pin to D6
#define ECHO_PIN_LEFT 9                                                             //Connect Echo pin to D7

//#define TRIGGER_PIN_FRONT 31                                                       //Connect Trig pin to D8
//#define ECHO_PIN_FRONT 30                                                          //Connect Echo pin to D9

#define p0 22                                                                       //Connect D22 to pin 2 of L923D                                                                       
#define p1 23                                                                       //Connect D23 to pin 7 of L923D         
#define p2 24                                                                       //Connect D24 to pin 15 of L923D
#define p3 25                                                                       //Connect D25 to pin 10 of L923D

int Rightdistance, Leftdistance, Frontdistance; 
long Rightduration, Leftduration, Frontduration;

void setup() 
{
  Serial.begin (9600);
 
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);
  //pinMode(TRIGGER_PIN_FRONT, OUTPUT);
  
  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  //pinMode(ECHO_PIN_FRONT, INPUT);
  
  pinMode(Q0, INPUT);
  pinMode(Q1, INPUT);
  pinMode(Q2, INPUT);
  pinMode(Q3, INPUT);
  
  pinMode(p0, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
}

void loop() 
{
  int Q0Sts = digitalRead(Q0);
  int Q1Sts = digitalRead(Q1);
  int Q2Sts = digitalRead(Q2);
  int Q3Sts = digitalRead(Q3);
/////////////////////////////////////////////////////////////////////////////
  
  digitalWrite(TRIGGER_PIN_RIGHT, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN_RIGHT, LOW);

  Rightduration = pulseIn(ECHO_PIN_RIGHT, HIGH);
  Rightdistance = (Rightduration/2)/29.1;

  Serial.print( "Right distance = ");
  Serial.println(Rightdistance);

//////////////////////////////////////////////////////////////////////

  digitalWrite(TRIGGER_PIN_LEFT, LOW);
  delay(2);

  digitalWrite(TRIGGER_PIN_LEFT, HIGH);
  delay(10);
  digitalWrite(TRIGGER_PIN_LEFT, LOW);

  Leftduration = pulseIn(ECHO_PIN_LEFT, HIGH);
  Leftdistance = (Leftduration/2)/29.1;

  Serial.print( "Left distance = ");
  Serial.println(Leftdistance);

//////////////////////////////////////////////////////////////////////

  /*digitalWrite(TRIGGER_PIN_FRONT, LOW);
  delay(2);

  digitalWrite(TRIGGER_PIN_FRONT, HIGH);
  delay(10);
  digitalWrite(TRIGGER_PIN_FRONT, LOW);

  Frontduration = pulseIn(ECHO_PIN_FRONT, HIGH);
  Frontdistance = (Frontduration/2)/29.1;

  Serial.print( "Front distance = ");
  Serial.println(Frontdistance);
*/
///////////////////////////////////////////////////////////////////////

if( Leftdistance>5 && Rightdistance>5)  ////////Frontdistance>5 &&
 {
   if(Q0Sts==0 && Q1Sts==1 && Q2Sts==0 && Q3Sts==1)
     backward_();
   else if(Q0Sts==1 && Q1Sts==0 && Q2Sts==1 && Q3Sts==0)
     forward_();
   else if(Q0Sts==0 && Q1Sts==1 && Q2Sts==1 && Q3Sts==0)
     left_();
   else if(Q0Sts==1 && Q1Sts==0 && Q2Sts==0 && Q3Sts==1)
     right_();
   else
     stop_();    
 }                                                                                                //////////////From here comes the code for obstacle avoidance
/*else if(Frontdistance<=5)
 {
  stop_();
  delay(200);
  backward_();
  stop_();
  delay(100);

  if(Leftdistance > Rightdistance)
    {
      left_();
      delay(250);
      stop_();
      delay(100);
    }
  else
    {
      right_();
      delay(250);
      stop_();
      delay(100);
    }
 }*/
else if (Leftdistance<=10 && Rightdistance<=10)
{
  backward_();
  delay(250);
  stop_();
  delay(100);
}

else if(Leftdistance<=10)
 {
  stop_();
  delay(100);
  backward_();
  delay(100);
  right_();
  delay(200);
  stop_();
  delay(100);
 }

else if(Rightdistance<=10)
 {
  stop_();
  delay(100);
  backward_();
  delay(250);
  left_();
  delay(250);
  stop_();
  delay(100);
 }
else if(Rightdistance<=10 && Leftdistance<=10 )
 {
  stop_();
  delay(100);
  backward_();
  delay(250);
  stop_();
  delay(100);
 
  if(Leftdistance > Rightdistance)
   {
    left_();
    delay(250);
    stop_();
    delay(100);
   }

   else
    {
      right_();
      delay(250);
      stop_();
      delay(100);
    }
 }
}


void stop_()
 {
  Serial.println("");
  Serial.println("STOP");
  digitalWrite(p0, LOW);
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
 }

void left_()
 {
  Serial.println("");
  Serial.println("LEFT");
  digitalWrite(p0, LOW);
  digitalWrite(p1, HIGH);
  digitalWrite(p2, HIGH);
  digitalWrite(p3, LOW);
 }

void right_()
 {
  Serial.println("");
  Serial.println("RIGHT");
  digitalWrite(p0, HIGH);
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, HIGH);
 }

void forward_()
 {
  Serial.println("");
  Serial.println("FORWARD");
  digitalWrite(p0, HIGH);
  digitalWrite(p1, LOW);
  digitalWrite(p2, HIGH);
  digitalWrite(p3, LOW);
 }

void backward_()
 {
  Serial.println("");
  Serial.println("BACKWARD");
  digitalWrite(p0, LOW);
  digitalWrite(p1, HIGH);
  digitalWrite(p2, LOW);
  digitalWrite(p3, HIGH);
 }
