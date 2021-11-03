#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "Wire.h"

//motor 1
int enA = 4;
int in1 = 5;
int in2 = 6;

//motor 2
int enB = 7;
int in3 = 8;
int in4 = 9;

TinyGPSPlus gps;
int turn_Speed = 175;                                            
int mtr_Spd = 250; 

void setup(){
  Serial1.begin(115200);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

unsigned long Distance_To_Home;                                    // variable for storing the distance to destination

int ac =0;                                                         // GPS array counter
int wpCount = 0;                                                   // GPS waypoint counter
double Home_LATarray[50];                                          // variable for storing the destination Latitude - Only Programmed for 5 waypoint
double Home_LONarray[50];                                          // variable for storing the destination Longitude - up to 50 waypoints


int increment = 0;

void setup() 
{  
  Serial.begin(115200);                                            // Serial 0 is for communication with the computer
  Serial1.begin(9600);                                             // Serial 1 is for Bluetooth communication - DO NOT MODIFY - JY-MCU HC-06 v1.40
  Serial2.begin(9600);                                             // Serial 2 is for GPS communication at 9600 baud - DO NOT MODIFY - Ublox Neo 6m 
  myservo.attach(9);                                               // attaches the servo to pin 9 (Servo 0 on the Adafruit Motor Control Board)
  
  pinMode(36, OUTPUT);                                             // define pin 36 as an output for an LED indicator - Not Used
  pinMode(bt_Pin, INPUT);                                          // This pin(34) is used to check the status of the Bluetooth connection - Not Used

  // Ping Sensor
  pinMode(trigPin, OUTPUT);                                        // Ping Sensor
  pinMode(echoPin, INPUT);                                         // Ping Sensor

  // Compass
  Wire.begin();                                                    // Join I2C bus used for the HMC5883L compass
  compass.begin();                                                 // initialize the compass (HMC5883L)
  compass.setRange(HMC5883L_RANGE_1_3GA);                          // Set measurement range  
  compass.setMeasurementMode(HMC5883L_CONTINOUS);                  // Set measurement mode  
  compass.setDataRate(HMC5883L_DATARATE_30HZ);                     // Set data rate  
  compass.setSamples(HMC5883L_SAMPLES_8);                          // Set number of samples averaged  
  compass.setOffset(0,0);                                          // Set calibration offset 

  Startup();                                                       // Run the Startup procedure on power-up one time
}

//********************************************************************************************************
// Main Loop

void loop()
{ 
  
                                           
  getGPS();                                                        // Update the GPS location
  getCompass();                                                    // Update the Compass Heading
  Ping();                                                          // Use at your own discretion, this is not fully tested

}
