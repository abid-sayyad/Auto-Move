/*
  Modified 28 November 2019, by LINGIB
  https://www.instructables.com/member/lingib/instructables/

  This function MUST be called each time through the loop as it updates
  the accelerometer, gyro, magnetometer, and quaternion values.
  In I2C mode we must poll the MPU9250 interrupt status register to see
  if the output data is ready.

  ---------------
  Terms of use:
  ---------------
  The software is provided "AS IS", without any warranty of any kind, express or implied,
  including but not limited to the warranties of mechantability, fitness for a particular
  purpose and noninfringement. In no event shall the authors or copyright holders be liable
  for any claim, damages or other liability, whether in an action of contract, tort or
  otherwise, arising from, out of or in connection with the software or the use or other
  dealings in the software. 
*/

void refresh_data()
{
  // ----- Poll the MPU9250 interrupt status in I2C mode
  if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {
    // ----- Read the accelerometer x|y|z register values
    myIMU.readAccelData(myIMU.accelCount);                                  // Read accelerometer register values

    // ----- Now we'll calculate the acceleration value into actual g's
    //       This depends on scale being set
    myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes;                     // Convert raw register value to milli-Gauss
    myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes;                     // Convert raw register value to milli-Gauss
    myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes;                     // Convert raw register value to milli-Gauss

    // ----- Read the gyro x|y|z register values
    myIMU.readGyroData(myIMU.gyroCount);                                    // Read gyro register values

    // ----- Calculate the gyro value into actual degrees per second
    //       This depends on scale being set
    myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;                      // Convert raw register value to dps  <-+   plus -ve sign for positive pitch
    myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;                      // Convert raw register value to dps  <-+--- gx & gy interchanged
    myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;                      // Convert raw register value to dps <----- applied -ve sign for CW rotation

    // Read the magnetometer x|y|z register values
    myIMU.readMagData(myIMU.magCount);                                      // Read magnetometer register values

    // ----- Calculate the magnetometer values in milliGauss and  apply
    //       the ASA fuse ROM values and milli-Gauss scale corrections
    //       The MPU92590 magnetometer uses the 14-bit scale-correction of 0.6
    myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes * myIMU.factoryMagCalibration[0] - myIMU.magBias[0];   // Convert/correct raw register value to milli-Gauss
    myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes * myIMU.factoryMagCalibration[1] - myIMU.magBias[1];   // Convert/correct raw register value to milli-Gauss
    myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes * myIMU.factoryMagCalibration[2] - myIMU.magBias[2];   // Convert/correct raw register value to milli-Gauss
  }

  // ----- This library function MUST be called before updating the Mahoney quaternions!
  myIMU.updateTime();

  /*
     The following quaternion values assume that the MPU-9250 gyro X-axis
     is pointing North and that the gyro Z-axis is pointing upwards.

     These values produce:
      - a clockwise heading of 0..360 degrees if we use the formula "Heading = atan2(myIMU.mx, myIMU.my;"
      - q0,q1,q2,q3 values of 1,0,0,0 when the compass is pointing north
  */

  MahonyQuaternionUpdate(  myIMU.ax,              -myIMU.ay,              myIMU.az,
                           myIMU.gx * DEG_TO_RAD, -myIMU.gy * DEG_TO_RAD, myIMU.gz * DEG_TO_RAD,
                           myIMU.my,              -myIMU.mx,              -myIMU.mz,
                           myIMU.deltat);

  //  MadgwickQuaternionUpdate( myIMU.ax,              -myIMU.ay,              myIMU.az,
  //                            myIMU.gx * DEG_TO_RAD, -myIMU.gy * DEG_TO_RAD, myIMU.gz * DEG_TO_RAD,
  //                            myIMU.my,              -myIMU.mx,              -myIMU.mz,
  //                            myIMU.deltat);

  // ----- calculate the pitch in degrees using Magwick quaternions
  myIMU.pitch = asin(2.0f * (*(getQ() + 1) * *(getQ() + 3) - *getQ() * *(getQ() + 2)));

  // ----- calculate the roll in degrees using Magwick quaternions
  myIMU.roll = -atan2(2.0f * (*getQ() * *(getQ() + 1) + * (getQ() + 2) * *(getQ() + 3)), *getQ() * *getQ() - * (getQ() + 1)
                      * *(getQ() + 1) - * (getQ() + 2) * *(getQ() + 2) + * (getQ() + 3) * *(getQ() + 3));

  // ----- calculate the yaw in degrees using Magwick quaternions
  myIMU.yaw = atan2(2.0f * (*(getQ() + 1) * *(getQ() + 2) + *getQ() * *(getQ() + 3)), *getQ() * *getQ() + * (getQ() + 1)
                    * *(getQ() + 1) - * (getQ() + 2) * *(getQ() + 2) - * (getQ() + 3) * *(getQ() + 3));
}
