
int decideMode() {

  if (mode == NORMAL) { //most of the decisions happen when current mode is normal
    
    signalLights(colorNormal);
    
    if (floorDist > floorOKThres) {
      mode = FLYING;
    }
    
    /*else if (frontDist < obstacleDistance && frontDist > 0) {
  
      mode = OBSTACLE;
      signalLights(colorObstacle);
         
      /*Passing by obstacle is a simple time based maneuver. Will just do these things in sequence.*
      turnRightHard();
      delay(obstaclePhase1);
      goStraight();
      delay(obstaclePhase2);
      turnLeftHard();
      delay(obstaclePhase3);
      goStraight();
      delay(obstaclePhase4);
      turnLeftHard();
      delay(obstaclePhase5);
      mode = GAP; //in gap mode goes straight until finding line again
      moveDirection = STRAIGHT;
    }*/

    else if (noOfLines==1) {
      mode = NORMAL;
      //Follow move direction that was decided on line sensor readings.
    }
  
    else if (noOfLines==0) {
      mode = GAP;
      moveDirection = STRAIGHT;//Override move direction from line sensors, probably not necessary because no lines were detected anyway.
    }
  
    /*else if (noOfLines==2) {
      //TODO: add additional check that the one line appeared on side.
      mode = PRELOOPCROSSING;
      //TODO: save direction from where new line appeared.
    }*/

    else if (noOfLines>1) { // more than two lines detected, assume start and finish markings //TEMP
      mode = ALLBLACK;
      //Follow move direction that was decided only on line sensor readings... hope this is sufficient
    }

  } //end of NORMAL mode decision options

  else if (mode == GAP) {
    signalLights(colorGap);
    
    if (noOfLines > 0) {//line found, exit
      mode = NORMAL;
      //Follow move direction that was decided on line sensor readings.
    }
    else {
      //Follow move direction that was decided on line sensor readings - it's straight if no line detected.
    }
  }

  else if (mode == PRELOOPCROSSING) {   
    //TODO: add additional check that the one line appeared on side and moves closer to other line.
    signalLights(colorPreloop);
    
    if (noOfLines == 1) { //two lines have gathered into one, assume loop knot
      mode = LOOPCROSSING;
      //Follow move direction that was decided on line sensor readings.
    }
    else {
      //Follow move direction that was decided on line sensor readings.
      //TODO direction adjustment, detect which is new line
    }
  }
  
  else if (mode == LOOPCROSSING) {
    signalLights(colorLoop);

    loopDirection = findLoopDirection(saveCounter);
    
    if (noOfLines == 2) { //two lines have separated assume got over knot part
      mode = AFTERLOOPCROSSING;
      //TODO direction adjustment based on the "new" line detected in PRELOOPCROSSING mode.
      
    }
    else {
      //Follow move direction that was decided only on line sensor readings.
    }
  }
  
  else if (mode == AFTERLOOPCROSSING) {
    signalLights(colorAfterloop);
    
    if (noOfLines == 1) { //Second line has left sight, back to normal mode.
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }
    else {
      //TODO direction adjustment based on the "new" line detected in PRELOOPCROSSING mode
    }
  }

  else if (mode == FLYING) {
    signalLights(colorFlying);
    if (floorDist <= floorOKThres) {
      mode = NORMAL;
    }
    else {
      moveDirection = STRAIGHT;//Override move direction from line sensors.
    }
  }

  else if (mode == ALLBLACK) {
    signalLights(colorAllblack);
    
    if (noOfLines < 2) {
      mode = NORMAL;
    }
    else {
      moveDirection = STRAIGHT;//Override move direction from line sensors.
    }
  }
  
}

/**
 * Detects on which side the additional black line appeared into view.
 * 
 * This function is called at loop crossing point. 
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
    
  }// /for

  if (leftmost > rightmost) {
    return LEFT;
  }
  else {
    return RIGHT;
  }
}

