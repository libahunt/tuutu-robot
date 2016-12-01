/**
 * Mode is set based on floor sensor, obstacle sensor readings and number of lines detected.
 * 
 * Saves into global variable: mode.
 */
int decideMode() {

  if (mode == NORMAL) { //most of the decisions happen when current mode is normal

    if (floorDist > floorOKThres) {
      mode = FLYING;
      lastMode = NORMAL;
    }
    
    else if (frontDist < obstacleDistance && frontDist > 0) {
      mode = OBSTACLE;
      lastMode = NORMAL;
    }

    else if (noOfLines==0) {
      mode = GAP;
      lastMode = NORMAL;
    }
  
    else if (noOfLines==2) {
      mode = PRELOOPCROSSING;
      lastMode = NORMAL;
      /* Save time to timeout if this is erroneus decision. */
      loopStartTime = millis();
    }

    else if (noOfLines>2) { // more than two lines detected, assume start and finish markings
      mode = ALLBLACK;
      lastMode = NORMAL;
    }

    /*if noOfLines==1
      stays in NORMAL mode
    */

  } //end of NORMAL mode decision options

  else if (mode == GAP) {

    if (floorDist > floorOKThres) {
      mode = FLYING;
      lastMode = GAP;
    }
    
    else if (noOfLines > 0) {//line found, exit from gap mode
      mode = NORMAL;
      lastMode = GAP;
    }

  }

  else if (mode == PRELOOPCROSSING) {
    
    if (noOfLines == 1) { //two lines have gathered into one, assume loop knot
      mode = LOOPCROSSING;
      lastMode = PRELOOPCROSSING;

      /* Analyze from which side the additional line appeared. */
      loopDirection = findLoopDirection(saveCounter);
      
      /* Save time to timeout if this is erroneus decision. */
      loopStartTime = millis();
    }

    /* Timeout into normal mode. */
    else if (millis() > loopStartTime + loopTimeout) {
      mode = NORMAL;
      lastMode = PRELOOPCROSSING;
    }

  }
  
  else if (mode == LOOPCROSSING) {
    
    if (noOfLines == 2) { //two lines have separated assume got over knot part
      mode = AFTERLOOPCROSSING;
      lastMode = LOOPCROSSING;      
    }

    /* Timeout into normal mode. */
    else if (millis() > loopStartTime + loopTimeout) {
      mode = NORMAL;
      lastMode = LOOPCROSSING;
    }
    
  }
  
  else if (mode == AFTERLOOPCROSSING) {
    
    if (noOfLines == 1) { //Second line has left sight, back to normal mode.
      mode = NORMAL;
      lastMode = AFTERLOOPCROSSING;
    }

    else if (noOfLines == 0) { //Second line has left sight, back to normal mode.
      mode = GAP;
      lastMode = AFTERLOOPCROSSING;
    }

  }

  else if (mode == FLYING) {
    
    if (floorDist <= floorOKThres) {
      mode = NORMAL;
      lastMode = FLYING;
    }
    
  }

  else if (mode == ALLBLACK) {
    
    if (floorDist > floorOKThres) {
      mode = FLYING;
      lastMode = ALLBLACK;
    }
    
    else if (noOfLines == 1) {
      mode = NORMAL;
      lastMode = ALLBLACK;
    }
    
    else if (noOfLines == 0); {
      mode = GAP;
      lastMode = ALLBLACK;
    }
  }

  /*Exiting from obstacle mode happens in main loop.*/
}



/**
 * Calculating move direction from detected lines.
 *
 * Saves into gloabal variables: leftSpeedCoef, rightSpeedCoef.
 */

void moveDirectionForLine() {
  
  int hasLineSum=0;
  for (i=0; i<9;i++) {
    hasLineSum += hasLine[i];
  }

  float leftWeight = (hasLine[0]*8 + hasLine[1]*4 + hasLine[2]*2 + hasLine[3]*1) * noOfLines / hasLineSum;
  float rightWeight = (hasLine[8]*8 + hasLine[7]*4 + hasLine[6]*2 + hasLine[5]*1) * noOfLines / hasLineSum;
  float hasLineDiff = abs(leftWeight - rightWeight);

  if (leftWeight > rightWeight) {
    leftSpeedCoef = -1 * (hasLineDiff - 4);
    rightSpeedCoef = leftWeight;
  }
  else if (leftWeight < rightWeight) {
    leftSpeedCoef = rightWeight;
    rightSpeedCoef = -1 * (hasLineDiff - 4);
  }
  
  
}


/**
 * Detects on which side an additional black line appeared into view.
 * 
 * This function is called at loop crossing point. 
 * Paramater currentSaveCounter - from which point backwards to analyze old readings.
 * Returns left or right as byte.
 */
byte findLoopDirection(int currentSaveCounter) {
  
  /*Count the readings in history that dont have any double line. This counter gets reset when second line appears. 
  It is used to find the point at which to drop the search because we have gone through double line phase end exited from it.*/
  int noDoubleLine = 0;
  /*Count the readings in history that do have double line. Used in combination with the previous counter to figure out wen to drop
  the search.*/
  int hasDoubleLine = 0;
  /*Counters for the steps that have line detected at the edges of the sensor*/
  int leftmost = 0;
  int rightmost = 0;
  /*History array index for the step back.*/
  int index;
  
  for (i=0; i<saveSize; i++) {

    /*Calculate history array index*/
    index = currentSaveCounter - i;    
    if (index < 0) {
      index = saveSize + currentSaveCounter - i;
    }

    /*Mark line situations into counters.*/
    if (noOfLinesPrev[index] >= 2) {
      noDoubleLine = 0;
      hasDoubleLine++;
      if (hasLinePrev[index][0]+hasLinePrev[index][1] > 0) {
        leftmost++;
      }
      if (hasLinePrev[index][9]+hasLinePrev[index][8] > 0) {
        rightmost++;
      }
    }
    else {
      noDoubleLine++;
    }

    /*If some edge lines data is gathered already and now one line situation has lasted a few steps, quit*/
    if (noDoubleLine>30 && hasDoubleLine > 10 && (leftmost>3 || rightmost >3) && (leftmost != rightmost)) {
      break;
    }
    
  }

  if (leftmost > rightmost) {
    return LEFT;
  }
  else {
    return RIGHT;
  }
}

