
int decide() {

  if (mode == NORMAL) { //most of the decisions happen when current mode is normal
    
    signalLights(colorNormal);
    
    if (floorDist > floorOKThres) {
      mode = FLYING;
    }

    else if (noOfLines==1) {
      mode = NORMAL;
      //Follow move direction that was decided on line sensor readings.
    }
    
    else if (frontDist < obstacleDistance && frontDist > 5) {
  
      mode = OBSTACLE;
      signalLights(colorObstacle);
         
      /*Passing by obstacle is a simple time based maneuver. Will just do these things in sequence.*/
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
    }
  
    else if (noOfLines == 0) {
      mode = GAP;
      moveDirection = STRAIGHT;//Override move direction from line sensors, probably not necessary because no lines were detected anyway.
    }
  
    else if (noOfLines==2) {
      //TODO: add additional check that the one line appeared on side.
      mode = PRELOOPCROSSING;
      //TODO: save direction from where new line appeared.
    }

    else if (noOfLines>2) { // more than two lines detected, assume start and finish markings
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
    
    if (noOfLines==1) { //two lines have gathered into one, assume loop knot
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
    
    if (noOfLines==2) { //two lines have separated assume got over knot part
      mode = AFTERLOOPCROSSING;
      //TODO direction adjustment based on the "new" line detected in PRELOOPCROSSING mode.
      
    }
    else {
      //Follow move direction that was decided only on line sensor readings.
    }
  }
  
  else if (mode == AFTERLOOPCROSSING) {
    signalLights(colorAfterloop);
    
    if (noOfLines==1) { //Second line has left sight, back to normal mode.
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }
    else {
      //TODO direction adjustment based on the "new" line detected in PRELOOPCROSSING mode
    }
  }

  else if (mode=FLYING) {
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
    
    if (noOfLines<2) {
      mode = NORMAL;
    }
    else {
      moveDirection = STRAIGHT;//Override move direction from line sensors.
    }
  }
  
}

