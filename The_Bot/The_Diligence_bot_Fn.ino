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

void setup() {
  Serial1.begin(115200);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}
