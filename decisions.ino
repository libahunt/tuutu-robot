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
      /*Find and save loop direction.*/
      loopDirection = findLoopDirection();
    }

    else if (noOfLines>2) { // more than two lines detected, assume start and finish markings
      mode = ALLBLACK;
    }

  }


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
  int leftCenterFifth = int(hasLine[2]) + int(hasLine[3]);
  int centerFifth = int(hasLine[4]);
  int rightCenterFifth = int(hasLine[5]) + int(hasLine[6]);
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
 * This function is called at loop crossing detection. 
 * Returns left or right as byte.
 */
byte findLoopDirection() {
  byte leftmost, rightmost;
  /*Find how far from left edge is the leftmost line.*/
  for (i=0; i<9; i++) {
    if (hasLine[i]) {
      leftmost = i;
      break;
    }
  }
  /*Find how far from right edge is the rightmost line.*/
  for (i=8; i>=0; i--) {
    if (hasLine[i]) {
      rightmost = 8-i;
      break;
    }
  }
  if (leftmost < rightmost) {
    return LEFT;
  }
  else {
    return RIGHT;
  }
 
}



/**
 * Chooses direction to follow one line out of two.
 * 
 * Takes preferred side as parameter.
 * Returns direction as byte.
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

