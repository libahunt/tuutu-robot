
void readSensors() {
  /**
   * Most usable global variables that will hold results after mesurement are:
   * hasLine[17] (bool)
   * noOfLines (int)
   * doubleLine (bool)
   * frontDist (int)
   * floorDist (float)
   */
  

  /*Get readings from sensors and save as black or gray decisions.*/
  for (i=0; i<9; i++) {
    sensorReadings[i] = analogRead(sensorPins[i]); 
    if (sensorReadings[i] > hasBlackThres) {
      hasBlack[i] = true;
      hasGray[i] = true;
    }
    else if (sensorReadings[i] > hasGrayThres) {
      hasGray[i] = true;
      hasBlack[i] = false;
    }
    else {
      hasBlack[i] = false;
      hasGray[i] = false;
    }
  
    delay(1);
  }

  /*Put probable line positions into an array and count lines.*/
  noOfLines = 0;
  for (i=0; i<9; i++) {
    if (hasBlack[i]) {
      hasLine[i*2] = true;
      noOfLines++;
    }
    else if (i<8 && hasGray[i] && hasGray[i+1]) {
      hasLine[i*2 + 1] = true;
      noOfLines++;
    }
    else if (i==8) {
      hasLine[i*2] = false;
    }
    else {
      hasLine[i*2] = false;
      hasLine[i*2 + 1] = false;
    }
  }

  /*When multiple lines, check if they are separated by white area*/
  if (noOfLines >=2) {
    int noOfGaps = -1;
    for (i=0; i<16; i++) {
      if (!hasLine[i] && hasLine[i+1]) {
        noOfGaps++;
      }
    }
    if (noOfGaps == 1) {
      doubleLine = true;
    }
  }
  

  /*Get reading from obstacle distance sensor.*/
  frontDist = obstacleSonar.ping_cm();

  /*Get reading from floor distance - mountain top sensor.*/
  floorDist = edgeSonar.ping_cm();

  int leftFifth = int(hasLine[0]) + int(hasLine[1]) + int(hasLine[2]);
  int leftCenterFifth = int(hasLine[3]) + int(hasLine[4]) + int(hasLine[5]) + int(hasLine[6]);
  int centerFifth = int(hasLine[7]) + int(hasLine[8]) + int(hasLine[9]);
  int rightCenterFifth = int(hasLine[13]) + int(hasLine[12]) + int(hasLine[11] + int(hasLine[10]));
  int rightFifth = int(hasLine[16]) + int(hasLine[15]) + int(hasLine[14]);

  if ((leftFifth + leftCenterFifth) == (rightFifth + rightCenterFifth)) {
     if (leftFifth > leftCenterFifth) {
      moveDirection = HARDLEFT;
    }
    else {
      moveDirection = SMOOTHLEFT;
    }
  }
  else if ((leftFifth + leftCenterFifth) > (rightFifth + rightCenterFifth)) {
    moveDirection = STRAIGHT;
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
  for (i=0; i<17; i++) {
    hasLinePrev[i][saveCounter] = hasLine[i];
  }
  noOfLinesPrev[saveCounter] = noOfLines;
  saveCounter++;
  if (saveCounter == saveSize) {
    saveCounter = 0;
  } 
  
} // /saveReadings



