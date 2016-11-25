
int decide() {

  if (mode == NORMAL) { //most of the decisions happen when current mode is normal
    
    if (floorDist > floorOKThres) {
      
      mode = FLYING;
      moveDirection = STRAIGHT;//Override move direction from line sensors.
      signalLights(colorFlying);
      
    }
    
    else if (frontDist < obstacleDistance && frontDist > 5) {
  
      mode = OBSTACLE;
      signalLights(colorObstacle);
         
      /*Passing by obstacle is a simple time based maneuver.*/
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
      signalLights(colorGap);
    }
  
    else if (noOfLines == 0) {
      mode = GAP;
      moveDirection = STRAIGHT;//Override move direction from line sensors, probably not necessary because no lines were detected anyway.
      signalLights(colorGap);
    }
  
    /*else if (noOfLines >=2 && doubleLine) {
      mode = PRELOOPCROSSING;
      //TODO: save direction from where new line appeared.
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorPreloop);
    }*/
  
    else if (noOfLines >=1) { // 1 or more line locations detected but not double line.
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }

    else if (noOfLines>2) { // more than two lines detected, assume start and finish markings
      mode = ALLBLACK;
      //Follow move direction that was decided only on line sensor readings... hope this is sufficient
      signalLights(colorAllblack);
    }

  } //end of NORMAL mode decision options

  else if (mode == GAP) {
    if (noOfLines > 0) {
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }
    else {
      moveDirection = STRAIGHT;//Override move direction from line sensors, probably not necessary because no lines were detected anyway.
      signalLights(colorGap);
    }
  }

  else if (mode == PRELOOPCROSSING) {
    if (noOfLines<=2 && !doubleLine) {
      mode = LOOPCROSSING;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorLoop);
    }
    else {
      //Follow move direction that was decided only on line sensor readings.
      //TODO direction adjustment, detect which is new line
      signalLights(colorPreloop);
    }
  }
  
  else if (mode == LOOPCROSSING) {
    if (noOfLines>=2 && doubleLine) {
      mode = AFTERLOOPCROSSING;
      //TODO direction adjustment based on the "new" line detected in PRELOOPCROSSING mode.
      signalLights(colorAfterloop);
    }
    else {
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorLoop);
    }
  }
  
  else if (mode == AFTERLOOPCROSSING) {
    if (noOfLines<=2 && !doubleLine) {
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }
    else {
      //TODO direction adjustment based on the "new" line detected in PRELOOPCROSSING mode
      signalLights(colorAfterloop);
    }
  }

  else if (mode=FLYING) {
    if (floorDist <= floorOKThres) {
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }
    else {
      moveDirection = STRAIGHT;//Override move direction from line sensors.
      signalLights(colorFlying);
    }
  }

  else if (mode == ALLBLACK) {
    if (noOfLines <=2 && !doubleLine) {
      mode = NORMAL;
      //Follow move direction that was decided only on line sensor readings.
      signalLights(colorNormal);
    }
    else {
      moveDirection = STRAIGHT;//Override move direction from line sensors.
      signalLights(colorAllblack);
    }
  }
  
}

