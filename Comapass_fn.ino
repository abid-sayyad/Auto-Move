#include "quaternionFilters.h"
#include "MPU9250.h"
#define I2Cclock 400000
#define I2Cport Wire
#define ADO 1
#if ADO
#define MPU9250_ADDRESS 0x69
#else 
#define MPU9250_ADDRESS 0x68
#define AK8932_ADDRESS 0x0C
#endif



MPU9250 myIMU(MPU9250_ADDRESS, I2Cport, I2Cclock);

/*
 * #define TASK 0 //caliberate eachtime at start up
 * #define TASK 1 //caliberate once using onboard code
 * #define TASK 2 //caliberate once using Processing "soft_cal.pde"
 * #define TASK 3 //display pitch, roll and heading on serial monitor (115200 baud)
 * #define TASK 4 //display heading using Processing "Compass_rose.pde" 
*/

#define TASK 2

float Mag_x_offset = -34.560013,
      Mag_y_offset = 528.885,
      Mag_z_offset = -125.259995,
      Mag_x_scale = 1.0247924,
      Mag_y_scale = 0.99078894,
      Mag_z_scale = 0.9853226;

#define True_North false
float Declination = 0.533333;

short MyLed = 13;

char InputChar;                             //incoming characters are stored in this var
bool LinkEstablished = false;               //receive indicator
String OutputString = "";                   //outgoing string to processing

//software timer
unsigned long Timer1 = 500000L;             // 500mS loop ... used when sending data to to Processing
unsigned long Stop1;                        // Timer1 stops when micros() exceeds this value

void setup ()
{
  Serial.begin(115200);
  while(!Serial);
  Wire.begin();
  Wire.setClock(400000);

  pinMode(MyLed, OUTPUT);
  digitalWrite(MyLed, HIGH);

  byte gyroID = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  if (!((gyroID == 0x71) || (gyroID == 0x73)))
  {
  Serial.print(F("WHO_AM_I = "));
    Serial.println(gyroID, HEX);
    Serial.println(F("Could not connect to the MPU9250/MPU9255"));
    Serial.println(F("Communication failed ... program aborted !!"));
    Serial.flush();
    abort();
  }
  else
  {
    // ----- MPU9250|MPU9255 found
    if (gyroID == 0x71) Serial.println(F("WHO_AM_I = 0x71\nMPU9250 is online ..."));
    if (gyroID == 0x73) Serial.println(F("WHO_AM_I = 0x73\nMPU9255 is online ..."));
    Serial.println("");

    // ----- Start by performing self test and reporting values
    myIMU.MPU9250SelfTest(myIMU.selfTest);
    Serial.print(F("x-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[0], 1); Serial.println("% of factory value");

    Serial.print(F("y-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[1], 1); Serial.println("% of factory value");

    Serial.print(F("z-axis self test: acceleration trim within : "));
    Serial.print(myIMU.selfTest[2], 1); Serial.println("% of factory value");

    Serial.print(F("x-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[3], 1); Serial.println("% of factory value");

    Serial.print(F("y-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[4], 1); Serial.println("% of factory value");

    Serial.print(F("z-axis self test: gyration trim within : "));
    Serial.print(myIMU.selfTest[5], 1); Serial.println("% of factory value");
    Serial.println("");

    Serial.println(F("Place the compass on a level surface"));
    Serial.println(F(""));

    delay(4000);                        // allow time to place the compass in position

    // ----- Calibrate gyro and accelerometers, load biases in bias registers
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

    // ----- Initialize device for active mode read of accelerometer, gyroscope, and
    //       temperature
    myIMU.initMPU9250();
    Serial.println(F("MPU9250 initialized for active data mode...."));
    Serial.println("");
  }
   // ----- Look for the AK8963 magnetometer
  byte MagID = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
  if (!(MagID == 0x48))
  {
    // ----- Communicati on failed, stop here
    Serial.print(F("WHO_AM_I = "));
    Serial.println(MagID, HEX);
    Serial.println(F("Could not connect to the AK8963"));
    Serial.println(F("Communication failed ... program aborted !!"));
    Serial.flush();
    abort();
  }
  else
  {
    // ----- AK8963 found
    Serial.println(F("WHO_AM_I = 0x48\nAK8963 is online ..."));
    Serial.println("");

    // ----- Get factory ASA calibration values
    myIMU.initAK8963(myIMU.factoryMagCalibration);

    // ----- Initialize device for active mode read of magnetometer
    Serial.println(F("AK8963 initialized for active data mode...."));
    Serial.println("");

    // ----- Display AK8963 fuse rom values
    Serial.println(F("AK8963 Fuse ROM values: "));
    Serial.print(F("ASAX: "));
    Serial.println(myIMU.factoryMagCalibration[0], 2);
    Serial.print(F("ASAY: "));
    Serial.println(myIMU.factoryMagCalibration[1], 2);
    Serial.print(F("ASAZ: "));
    Serial.println(myIMU.factoryMagCalibration[2], 2);
    Serial.println("");

    // ----- Get correct sensor resolutions (You only need to do this once)
    myIMU.getAres();      // milli-gravity
    myIMU.getGres();      // dps
    myIMU.getMres();      // milli-Gauss 14-bit|16-bit

    // ---- display sensor scale multipliers
    Serial.println(F("Sensor-scale multipliers"));
    Serial.print(F("accel: "));
    Serial.println(myIMU.aRes, 6);
    Serial.print(F(" gyro: "));
    Serial.println(myIMU.gRes, 6);
    Serial.print(F("  mag: "));
    Serial.println(myIMU.mRes, 6);
    Serial.println("");
  }
    if ((TASK == 0) || (TASK == 1))
    {
          myIMU.magCalMPU9250(myIMU.magBias, myIMU.magScale);
    }
      if (TASK == 1)
  {
    // ----- Message
    Serial.println(F("------------------------------------------"));
    Serial.println(F("Copy-&-paste the following code into your "));
    Serial.println(F("Arduino header then delete the old code."));
    Serial.println(F("------------------------------------------"));
    Serial.println(F(""));
    Serial.println(F("float"));
    Serial.print(F("Mag_x_offset = "));
    Serial.print(myIMU.magBias[0]);
    Serial.println(",");
    Serial.print(F("Mag_y_offset = "));
    Serial.print(myIMU.magBias[1]);
    Serial.println(",");
    Serial.print(F("Mag_z_offset = "));
    Serial.print(myIMU.magBias[2]);
    Serial.println(",");
    Serial.print(F("Mag_x_scale = "));
    Serial.print(myIMU.magScale[0]);
    Serial.println(",");
    Serial.print(F("Mag_y_scale = "));
    Serial.print(myIMU.magScale[1]);
    Serial.println(",");
    Serial.print(F("Mag_z_scale = "));
    Serial.print(myIMU.magScale[2]);
    Serial.println(F(";"));

    // ----- Halt program
    while (true);
  }
      if ((TASK == 3) || (TASK == 4) || (TASK == 5))
  {
    // ----- Copy the hard-iron offsets
    myIMU.magBias[0] = Mag_x_offset;
    myIMU.magBias[1] = Mag_y_offset;
    myIMU.magBias[2] = Mag_z_offset;

    // ----- Copy the soft-iron scalefactors
    myIMU.magScale[0] = Mag_x_scale;
    myIMU.magScale[1] = Mag_y_scale;
    myIMU.magScale[2] = Mag_z_scale;

    // ----- Display offsets & scale-factors
    Serial.println("");
    Serial.print("Mag_x_offset = ");
    Serial.println(myIMU.magBias[0]);
    Serial.print("Mag_y_offset = ");
    Serial.println(myIMU.magBias[1]);
    Serial.print("Mag_z_offset = ");
    Serial.println(myIMU.magBias[2]);
    Serial.print("Mag_x_scale = ");
    Serial.println(myIMU.magScale[0]);
    Serial.print("Mag_y_scale = ");
    Serial.println(myIMU.magScale[1]);
    Serial.print("Mag_z_scale = ");
    Serial.println(myIMU.magScale[2]);
    Serial.println("");
  }

  // -----------------------------------------------------------------
  // TASK 3,4 ... common message
  // -----------------------------------------------------------------
  if ((TASK == 3) || (TASK == 4))
  {

  }

  // -----------------------------------------------------------------
  // TASK 5 ... message
  // -----------------------------------------------------------------
  if (TASK == 5)
  {

  }

  // ----- start software timer
  Stop1 = micros() + Timer1;                            // Used by send_data() function
 
}

void loop()
{
  refresh_data();                                       // this must be done each time through the loop

  // ----- Processing Tasks
  switch (TASK) {
    case 2:
      compass_cal();                                    // Get compass offsets and scale-factors using Processing "compass_cal.pde" (circle-method)
      break;
    case 5:
      compass_rose();                                   // Display compass heading using Processing "compass_rose.pde"
      break;
    default:
      break;
  }

  // ----- Perform these tasks every 500mS
  if (micros() > Stop1)
  {
    Stop1 += Timer1;                                    // Reset timer

    // ----- Serial Monitor Tasks
    switch (TASK) {
      case 0:
        break;
      case 3:
        break;
      case 4:
        display_compass_heading_on_serial_monitor();    // Display compass pitch roll & heading on Serial Monitor (115200 bauds)
        break;
      default:
        break;
    }
  }
}
