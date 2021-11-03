#define forward 300 // Change this value to change senstivity for forward direction /-Default 340-/ *X*
#define backward 355 // Change this value to change senstivity for backward direction /-Default 400-/ *X*
#define left 324 // Change this value to change senstivity for left direction /-Default 340-/ *Y*
#define right 350 // Change this value to change senstivity for right direction /-Default 400-/ *Y*

int GNDPin=A5; //Set Analog pin 4 as GND
int VccPin=A1; //Set Analog pin 5 as VCC
int xPin=A2; //X axis input
int yPin=A3; //Y axis input
int zPin=A4; //Z axis input(not used)
int Q1=10,Q2=11,Q3=12,Q4=13; //Output pins to be connected to 10, 11, 12, 13 of Decoder IC

long x; //Variabe for storing X coordinates
long y; //Variabe for storing Y coordinates
long z; //Variabe for storing Z coordinates

void setup()
{
  Serial.begin(9600);
  pinMode(Q1,OUTPUT);
  pinMode(Q2,OUTPUT);
  pinMode(Q3,OUTPUT);
  pinMode(Q4,OUTPUT);
  pinMode(GNDPin, OUTPUT);
  pinMode(VccPin, OUTPUT);
  digitalWrite(GNDPin, LOW); //Set A4 pin LOW
  digitalWrite(VccPin, HIGH); //Set A5 pin HIGH
}

void loop()
{
  x = analogRead(xPin); //Reads X coordinates
  y = analogRead(yPin); //Reads Y coordinates
  z = analogRead(zPin); //Reads Z coordinates (Not Used)

    if(x<forward)      // Change the value for adjusting sensitivity  
      forward_();
    else if(x>backward) // Change the value for adjusting sensitivity
      backward_();
    else if(y>right) // Change the value for adjusting sensitivity
      right_();
    else if(y<left) // Change the value for adjusting sensitivity
      left_();
    else
      stop_();
}

void stop_()
{
  Serial.println("");
  Serial.println("STOP");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,LOW);
}

void forward_()
{
  Serial.println("");
  Serial.println("Forward");
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
}

void backward_()
{
  Serial.println("");
  Serial.println("Backward");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,HIGH);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,HIGH);
}

void left_()
{
  Serial.println("");
  Serial.println("Left");
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,HIGH);
  digitalWrite(Q3,HIGH);
  digitalWrite(Q4,LOW);
}

void right_()
{
  Serial.println("");
  Serial.println("Right");
  digitalWrite(Q1,HIGH);
  digitalWrite(Q2,LOW);
  digitalWrite(Q3,LOW);
  digitalWrite(Q4,HIGH);
}
