
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
   *
  int leftEdge = int(hasLine[0]) + int(hasLine[1]);
  int leftCenter = int(hasLine[2]) + int(hasLine[3]);
  int center = int(hasLine[4]);
  int rightCenter = int(hasLine[5]) + int(hasLine[6]);
  int rightEdge = int(hasLine[7]) + int(hasLine[8]);

  

  if (leftEdge + leftCenter > rightCenter + rightEdge) {
    if (leftEdge>0 && rightEdge==0 && rightCenter==0) {
      moveDirection=HARDLEFT;
    }
    else {
      moveDirection=SMOOTHLEFT;
    }
  }
  else if (leftEdge + leftCenter < rightCenter + rightEdge) {
    if (rightEdge > 0 && leftEdge==0 && leftCenter==0) {
      moveDirection=HARDRIGHT;
    }
    else {
      moveDirection=SMOOTHRIGHT;
    }
  }
  else {
    moveDirection=STRAIGHT;
  }
  */

  
  
} // /readSensors



void saveReadings() {
  
  /*save line existence states*/
  for (i=0; i<9; i++) {
    hasLinePrev[saveCounter][i] = hasLine[i];
  }
  noOfLinesPrev[saveCounter] = noOfLines;
  saveCounter++;
  if (saveCounter == saveSize) {
    saveCounter = 0;
  } 
  
} // /saveReadings


/*Alternative sensor reading into movedirection math.*/

void chooseDirection() {
  
  int hasLineSum=0;
  for (i=0; i<9;i++) {
    hasLineSum += hasLine[i];
  }

  float leftWeight = (hasLine[0]*8 + hasLine[1]*4 + hasLine[2]*2 + hasLine[3]*1) * noOfLines / hasLineSum;
  float rightWeight = (hasLine[8]*8 + hasLine[7]*4 + hasLine[6]*2 + hasLine[5]*1) * noOfLines / hasLineSum;
  float hasLineDiff = leftWeight - rightWeight;
  
  leftSpeedCoef = hasLineDiff;
  rightSpeedCoef = -1* hasLineDiff;
  
}

