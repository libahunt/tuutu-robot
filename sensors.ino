
/**
 * Fills following global variables with values:
 * sensorReadings[9] (int)
 * hasLine[9] (bool)
 * noOfLines (int)
 * frontDist (int)
 * floorDist (float)
 */
void readSensors() {
 
  noOfLines = 0;
  for (i=0; i<9; i++) {
    /*Get analog reading.*/
    sensorReadings[i] = analogRead(sensorPins[i]); 
    if (sensorReadings[i] > hasBlackThres) {
      /*Save if it's presumably black or not.*/
      hasLine[i] = true;
      /*If first sensor is black it it first separate line.
      For other sensors the previous slot has to be white to count it a beginning of another line.*/
      if (i==0) {
        noOfLines++;
      }
      else {
        if (!hasLine[i-1]) {
          noOfLines++;
        }
      }
    }
    else {
      hasLine[i] = false;
    }   
    delay(1);//Delay for more stable analog readings.
  }
  

  /*Get reading from obstacle distance sensor.*/
  frontDist = obstacleSonar.ping_cm();

  /*Get reading from floor distance - mountain top sensor.*/
  floorDist = edgeSonar.ping_cm();
  
} // /readSensors



void saveReadings() {
  
  /*Save line existence states.*/
  for (i=0; i<9; i++) {
    hasLinePrev[saveCounter][i] = hasLine[i];
  }
  /*Save number of detected separate lines.*/
  noOfLinesPrev[saveCounter] = noOfLines;
  
  saveCounter++;
  if (saveCounter == saveSize) {
    saveCounter = 0;
  } 
  
} // /saveReadings




