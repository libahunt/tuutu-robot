
int decide() {

  if (mode == NORMAL) { //most of the decisions happen when current mode is normal
    
    signalLights(colorNormal);
    
    if (floorDist > floorOKThres) {
      
      mode = FLYING;
      moveDirection = STRAIGHT;
      
    }
    
    else if (frontDist < obstacleDistance && frontDist > 10) {
  
      mode = OBSTACLE;
         
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
    }
  
    else if (noOfLines == 0) {
      mode = GAP;
      moveDirection = STRAIGHT;
    }
  
    else if (noOfLines >=2 && doubleLine) {
      mode = PRELOOPCROSSING;
      
    }
  
    else if (noOfLines >=1) { // 1 or more line locations detected but not double line. Turn towards more black ...
      mode = NORMAL;
    }

    else if (noOfLines>2) { // even black on both sides, assume start and finish markings
      mode = ALLBLACK;
    }

  } //end of NORMAL mode decision options

  else if (mode == GAP) {
    if (noOfLines > 0) {
      mode = NORMAL;
      //return to other if statements
      moveDirection = STRAIGHT;
    }
    else {
      moveDirection = STRAIGHT;
    }
  }

  else if (mode == PRELOOPCROSSING) {
    if (noOfLines<=2 && !doubleLine) {
      mode = LOOPCROSSING;
      //return to other if statements
    }
    else {
      //TODO direction adjustment, detect which is new line
    }
  }
  
  else if (mode == LOOPCROSSING) {
    if (noOfLines>=2 && doubleLine) {
      mode = AFTERLOOPCROSSING;
      //return to other if statements
    }
    else {
      //TODO direction adjustment
    }
  }
  
  else if (mode == AFTERLOOPCROSSING) {
    if (noOfLines<=2 && !doubleLine) {
      mode = NORMAL;
      //return to other if statements
    }
    else {
      //TODO direction adjustment, choose direction to leave the loop to same side as new line came
    }
  }

  else if (mode=FLYING) {
    if (floorDist <= floorOKThres) {
      mode = NORMAL;
      //return to other if statements
    }
    else {
      moveDirection = STRAIGHT;
    }
  }

  else if (mode == ALLBLACK) {
    //TODO check if not even black any more
    //return to NORMAL
    //else goStraight()
  }
}

/**
 * NORMAL - blue
 * GAP - white
 * PRELOOPCROSSING orange
 * LOOPCROSSING red
 * AFTERLOOPCROSSING purple
 * OBSTACLE 
 * FLYING
 * ALLBLACK
 */

