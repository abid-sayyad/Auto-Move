void display_compass_heading_on_serial_monitor()
{
  //  // ----- display sample rate (Hz)
  //  Serial.print("rate ");
  //  printNumber((float)myIMU.sumCount / myIMU.sum);

  // ----- display quaternions
  Serial.print(" |   q0|qx|qy|qz ");
  printNumber(*getQ());
  printNumber(*(getQ() + 1));
  printNumber(*(getQ() + 2));
  printNumber(*(getQ() + 3));

  //  // ----- display accelerometer xyz in milli-gravities (mg)
  //  Serial.print(" |   accel ");
  //  printNumber((short)(myIMU.ax * 1000));
  //  printNumber((short)(myIMU.ay * 1000));
  //  printNumber((short)(myIMU.az * 1000));

  //  // ----- display gyro xyz in degrees/sec (dps)
  //  Serial.print(" |   gyro ");
  //  printNumber((short)(myIMU.gx));
  //  printNumber((short)(myIMU.gy));
  //  printNumber((short)(myIMU.gz));

  //  // ----- display magnetometer xyz in milliGausss (mG)
  //  Serial.print(" |   mag ");
  //  printNumber((short)myIMU.mx);
  //  printNumber((short)myIMU.my);
  //  printNumber((short)myIMU.mz);

  //  // ----- display pitch/roll/yaw in degrees (deg)
  //  Serial.print(" |   p/r/yaw ");
  //  printNumber((short)myIMU.pitch);
  //  printNumber((short)myIMU.roll);
  //  float yaw = myIMU.yaw;
  //  if (yaw > 360.0) yaw -= 360.0;
  //  if (yaw < 0.0) yaw += 360.0;
  //  printNumber((short)yaw);

  //  // ----- display the compass heading in degrees (float)
  //  Serial.print(" |   Heading: ");
  //  printNumber(Heading);

  // ----- display the pitch
  Serial.print(" |   Pitch: ");
  printNumber((short)(round(myIMU.pitch * RAD_TO_DEG)));

  // ----- display the roll
  Serial.print(" |   Roll: ");
  printNumber((short)(round(myIMU.roll * RAD_TO_DEG)));

  /*
     For all practical purposes the compass yaw and compass heading are the same
  */

  // ----- display the heading
  Serial.print(" |   Heading: ");
  float heading = myIMU.yaw * RAD_TO_DEG;
  if (heading < 0) heading += 360.0;              // Yaw goes negative between 180 amd 360 degrees
  if (True_North == true) heading += Declination; // calculate True North
  if (heading < 0) heading += 360.0; 
  if (heading > 360) heading -= 360.0;
  printNumber((short)(round(heading)));

  // ----- line ending
  Serial.println("");
}
