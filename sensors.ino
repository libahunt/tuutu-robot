
void readSensors() {
  /**
   * Most usable global variables that will hold results after mesurement are:
   * sensorReadings[9] (int)
   * hasLine[9] (bool)
   * noOfLines (int)
   * frontDist (int)
   * floorDist (float)
   */
  

  /*Get readings from sensors save them and also save as "has line" boolean. 
  Count lines - black areas separated by white.*/
  noOfLines = 0;
  for (i=0; i<9; i++) {
    sensorReadings[i] = analogRead(sensorPins[i]); 
    if (sensorReadings[i] > hasBlackThres) {
      hasLine[i] = true;
      if (i==0) {
        noOfLines++;//if first sensor is black it it first separate line
      }
      else {
        if (!hasLine[i-1]) {//if previous sensor was white
          noOfLines++;//this counts as new separate line
        }
      }
    }
    else {
      hasLine[i] = false;
    }
    delay(1);//delay for more stable analog readings
  }
  

  /*Get reading from obstacle distance sensor.*/
  frontDist = obstacleSonar.ping_cm();

  /*Get reading from floor distance - mountain top sensor.*/
  floorDist = edgeSonar.ping_cm();

  /**
   * Calculate which way to move to keep on the line(s) that were detected.
   * In some modes this decision will be overridden.
   */
  int leftFifth = int(hasLine[0]) + int(hasLine[1]);
  int leftCenterFifth = int(hasLine[2]) + int(hasLine[3]);
  int centerFifth = int(hasLine[4]);
  int rightCenterFifth = int(hasLine[5]) + int(hasLine[6]);
  int rightFifth = int(hasLine[7]) + int(hasLine[8]);

  if ((leftFifth + leftCenterFifth) > (rightFifth + rightCenterFifth)) {
     if (leftFifth > leftCenterFifth) {
      moveDirection = HARDLEFT;
    }
    else {
      moveDirection = SMOOTHLEFT;
    }
  }
  else if ((leftFifth + leftCenterFifth) == (rightFifth + rightCenterFifth)) {
    if (leftFifth > rightFifth) {
      moveDirection = SMOOTHLEFT;
    }
    else if (rightFifth > leftFifth) {
      moveDirection = SMOOTHRIGHT;
    }
    else {
      moveDirection = STRAIGHT;
    }
  }
  else if ((leftFifth + leftCenterFifth) < (rightFifth + rightCenterFifth)) {
    if (rightFifth > rightCenterFifth) {
      moveDirection = HARDRIGHT;
    }
    else {
      moveDirection = SMOOTHRIGHT;
    }
  }
  
  
} // /readSensors



void saveReadings() {
  
  /*save line existence states*/
  for (i=0; i<9; i++) {
    hasLinePrev[i][saveCounter] = hasLine[i];
  }
  noOfLinesPrev[saveCounter] = noOfLines;
  saveCounter++;
  if (saveCounter == saveSize) {
    saveCounter = 0;
  } 
  
} // /saveReadings



