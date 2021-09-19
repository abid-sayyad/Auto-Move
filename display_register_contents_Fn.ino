/*


  This routine displays the the MPU-9250 register contents
  on your serial monitor (115200 bauds)

*/

void display_register_contents_on_serial_monitor() {

  // ----- display accelerometer xyz in milli-gravities (mg)
  Serial.print(" |   accel ");
  printNumber((short)(myIMU.ax * 1000));
  printNumber((short)(myIMU.ay * 1000));
  printNumber((short)(myIMU.az * 1000));

  // ----- display gyro xyz in degrees/sec (dps)
  Serial.print(" |   gyro ");
  printNumber((short)(myIMU.gx));
  printNumber((short)(myIMU.gy));
  printNumber((short)(myIMU.gz));

  // ----- display magnetometer xyz in milliGausss (mG)
  Serial.print(" |   mag ");
  printNumber((short)myIMU.mx);                                       // magX, magY, magZ
  printNumber((short)myIMU.my);
  printNumber((short)myIMU.mz);
  Serial.print("");

  // ----- Read the temperature adc values
  myIMU.tempCount = myIMU.readTempData();

  // -----  Calculate the temperature in degrees Centigrade
  myIMU.temperature = ((float) myIMU.tempCount) / 333.87 + 21.0;      // Where does this formula come from ?

  // ----- Print temperature in degrees Centigrade
  Serial.print(" |   temp ");
  printNumber(myIMU.temperature);
  Serial.println("");
}
