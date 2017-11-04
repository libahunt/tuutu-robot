
/**
 * Fills following global variables with values:
 * sensorReadings[9] (int)
 * hasLine[9] (bool)
 * noOfLines (int)
 * lineWidth (int)
 * frontDist (int)
 * floorDist (float)
 */
void readSensors() {
 
  noOfLines = 0;
  lineWidth = 0;
  int currentLineWidth = 0;
  for (i=0; i<9; i++) {
    /*Get analog reading.*/
    sensorReadings[i] = analogRead(sensorPins[i]); 
    if (sensorReadings[i] > hasBlackThres) {
      /*Save if it's presumably black or not.*/
      hasLine[i] = true;
      lineWidth++;
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
      /*If last sensor happened to have line then there is a lineWidth value present.
      Compare it to the maximum line width seen and replace the max if bigger.
      If last sensor did not have line then lineWidth is 0 and nothing much happens here.*/
      if (currentLineWidth > lineWidth) { 
        lineWidth = currentLineWidth;
      }
      currentLineWidth = 0;
    }   
    delay(1);//Delay for more stable analog readings.
  }
  

  /*Get reading from obstacle distance sensor.*/
  frontDist = obstacleSonar.ping_cm();

  /*Get reading from floor distance - mountain top sensor.*/
  floorDist = edgeSonar.ping_cm();
  
}



/**
 * Saves sensor readings into history array.
 * 
 * The array gets overwritten after fillig up. saveCounter keeps track of current position.
 */
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
  
}

