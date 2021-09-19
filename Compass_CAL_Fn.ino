void compass_cal()
{
  // ----- Locals
  float
  xPos,
  yPos,
  zPos;

  // ----- read input character
  if (Serial.available()) {
    InputChar = Serial.read();
    if ((InputChar == 's') || (InputChar == 'S')) {
      LinkEstablished = true;
    }
  }

  // -----Read the magnetometer x|y|z register values
  myIMU.readMagData(myIMU.magCount);

  // ----- calculate the magnetometer values (no offsets)
  xPos = (float)myIMU.magCount[0] * myIMU.factoryMagCalibration[0] * myIMU.mRes;   // raw mx * ASAX * 0.6 (mG)
  yPos = (float)myIMU.magCount[1] * myIMU.factoryMagCalibration[1] * myIMU.mRes;   // raw my * ASAY * 0.6 (mG)
  zPos = (float)myIMU.magCount[2] * myIMU.factoryMagCalibration[2] * myIMU.mRes;   // raw mz * ASAZ * 0.6 (mG)

  // ------ create output data string
  OutputString = String(xPos) + ',' + String(yPos) + ',' + String(zPos);

  // ----- send string if link established
  if (LinkEstablished && ((InputChar == 's') || (InputChar == 'S'))) {
    InputChar = 'x';
    Serial.println(OutputString);
  }

  // ----- send 'S' if link not established
  if (micros() > Stop1) {
    Stop1 += Timer1;
    if (!LinkEstablished) {
      Serial.println('S');
    }
  }
}
