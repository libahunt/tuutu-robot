/**
 * Mode is set based on floor sensor, obstacle sensor readings and number of lines detected.
 * 
 * Saves into global variable: mode.
 */
int decideMode() {

  if (mode == NORMAL) { //most of the decisions happen when current mode is normal

    if (floorDist > floorOKThres) {
      mode = FLYING;
    }
    
    else if (frontDist < obstacleDistance && frontDist > 0) {
      mode = OBSTACLE;
    }

    else if (noOfLines==0) {
      mode = GAP;
    }

    /*If noOfLines==1 stays in NORMAL mode.*/
  
    else if (noOfLines==2) {
      mode = PRELOOPCROSSING;
      /* Save time to timeout if this is erroneus decision. */
      loopStartTime = millis();
    }

    else if (noOfLines>2) { // more than two lines detected, assume start and finish markings
      mode = ALLBLACK;
    }

  } //end of NORMAL mode decision options


  else if (mode == GAP) {

    if (floorDist > floorOKThres) {
      mode = FLYING;
    }
    
    else if (noOfLines > 0) {//line found, exit from gap mode
      mode = NORMAL;
    }

  }


  else if (mode == PRELOOPCROSSING) {

    /*Two lines have gathered into one, assume loop knot.*/
    if (noOfLines == 1) { 
      mode = LOOPCROSSING;

      /*Analyze from which side the additional line appeared.*/
      loopDirection = findLoopDirection(saveCounter);
      
      /*Save time to timeout if this is erroneus decision.*/
      loopStartTime = millis();
    }

    /*Timeout into normal mode.*/
    else if (millis() > loopStartTime + loopTimeout) {
      mode = NORMAL;
    }

  }

  
  else if (mode == LOOPCROSSING) {

    /*Two lines have separated assume got over knot part.*/
    if (noOfLines == 2) { 
      mode = AFTERLOOPCROSSING;    
    }

    /*Timeout into normal mode.*/
    else if (millis() > loopStartTime + loopTimeout) {
      mode = NORMAL;
    }
    
  }
  
  else if (mode == AFTERLOOPCROSSING) {

    /*Second line has left sight, back to normal mode.*/
    if (noOfLines == 1) { 
      mode = NORMAL;
    }

    /*Backup to exit the state in case something went wrong meanwhile.*/ 
    else if (noOfLines == 0) { 
      mode = GAP;
    }

  }
  

  else if (mode == FLYING) {
    
    if (floorDist <= floorOKThres) {
      mode = NORMAL;
    }
    
  }
  

  else if (mode == ALLBLACK) {
    
    if (floorDist > floorOKThres) {
      mode = FLYING;
    }
    
    else if (noOfLines == 1) {
      mode = NORMAL;
    }
    
    else if (noOfLines == 0); {
      mode = GAP;
    }
  }

  /*Exiting from obstacle mode into gap mode happens in main loop because it is simple time based action.*/
  
}



/**
 * Calculating move direction from detected lines.
 */

byte getLineDirection() {
  
  byte lineDirection;

  int leftFifth = int(hasLine[0]) + int(hasLine[1]);
  int leftCenterFifth = int(hasLine[2]);
  int centerFifth = int(hasLine[3]) + int(hasLine[4]) + int(hasLine[5]);
  int rightCenterFifth = int(hasLine[6]);
  int rightFifth = int(hasLine[7]) + int(hasLine[8]);

  if ((leftFifth + leftCenterFifth) > (rightFifth + rightCenterFifth)) {
     if (leftFifth >= leftCenterFifth) {
      lineDirection = HARDLEFT;
    }
    else {
      lineDirection = SMOOTHLEFT;
    }
  }
  else if ((leftFifth + leftCenterFifth) == (rightFifth + rightCenterFifth)) {
    if (leftFifth > rightFifth) {
      lineDirection = SMOOTHLEFT;
    }
    else if (rightFifth > leftFifth) {
      lineDirection = SMOOTHRIGHT;
    }
    else {
      lineDirection = STRAIGHT;
    }
  }
  else if ((leftFifth + leftCenterFifth) < (rightFifth + rightCenterFifth)) {
    if (rightFifth >= rightCenterFifth) {
      lineDirection = HARDRIGHT;
    }
    else {
      lineDirection = SMOOTHRIGHT;
    }
  }
  
  return lineDirection;
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



/**
 * Chooses direction to follow one line out of two.
 */
byte moveDirectionForOneLine(byte chosenDirection) {
  byte line;
  if (chosenDirection == LEFT) {
    /*Find leftmost line.*/
    for (i=0; i<9; i++) {
      if (hasLine[i]) {
        line = i;
        break;
      }
    }
  }
  else { //chosenDirection == RIGHT
    /*Find rightmost line.*/
    for (i=8; i>=0; i--) {
      if (hasLine[i]) {
        line = i;
        break;
      }
    }
  }

  /*Return direction.*/
  if (line<=1) {
    return HARDLEFT;
  }
  else if (line==2) {
    return SMOOTHLEFT;
  }
  else if (line>=3 && line<=5) {
    return STRAIGHT;
  }
  else if (line==6) {
    return SMOOTHRIGHT;
  }
  else {
    return HARDRIGHT;
  }
} 

