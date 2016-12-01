void moveDir(int moveDirection) {
  if (moveDirection == HARDLEFT) {
    turnLeftHard();
  }
  else if (moveDirection == SMOOTHLEFT) {
    turnLeft();
  }
  else if (moveDirection == STRAIGHT) {
    goStraight();
  }
  else if (moveDirection == SMOOTHRIGHT) {
    turnRight();
  }
  else if (moveDirection == HARDRIGHT) {
    turnRightHard();
  }
}
  
void goStraight() { 
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, speedPWM);
  analogWrite(motorLeftRv, 0);
}

void goStraightSlow() { 
  analogWrite(motorRightFw, speedSlowPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, speedSlowPWM);
  analogWrite(motorLeftRv, 0);
}

void turnLeft() {
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, 0);
}

void turnRight() {
  analogWrite(motorRightFw, 0);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, speedPWM);
  analogWrite(motorLeftRv, 0);
}

void turnLeftHard() {
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, hardTurnPWM);
}

void turnRightHard() {
  analogWrite(motorRightFw, 0);
  analogWrite(motorRightRv, hardTurnPWM);
  analogWrite(motorLeftFw, speedPWM);
  analogWrite(motorLeftRv, 0);
}


void stopMotors() {
  analogWrite(motorRightFw, 0);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, 0);
}



/*Alternative motors control.*/

void moveMotors(int maxPWM, float leftSpeedCoef, float rightSpeedCoef) {
  /*Coeficent parameters can be negative too for reversing movement.*/
    int leftSpeed, rightSpeed, leftFwPWM, leftRvPWM, rightFwPWM, rightRvPWM;
    if (abs(leftSpeedCoef) > abs(rightSpeedCoef)) {
      leftSpeed = maxPWM;
      rightSpeed = maxPWM * rightSpeedCoef/leftSpeedCoef;
    }
    else if (abs(leftSpeedCoef) < abs(rightSpeedCoef)) {
      leftSpeed = maxPWM * leftSpeedCoef/rightSpeedCoef;
      rightSpeed = maxPWM;
    }
    else {
      leftSpeed = maxPWM;
      rightSpeed = maxPWM;
    }

    if (leftSpeed >= 0) {
      leftFwPWM = leftSpeed;
      leftRvPWM = 0;
    }
    else {
      leftFwPWM = 0;
      leftRvPWM = -1*leftSpeed;
    }
    if (rightSpeed >= 0) {
      rightFwPWM = rightSpeed;
      rightRvPWM = 0;
    }
    else {
      rightFwPWM = 0;
      rightRvPWM = -1*rightSpeed;
    }

    analogWrite(motorLeftFw, leftFwPWM);
    analogWrite(motorLeftRv, leftRvPWM);
    analogWrite(motorRightFw, rightFwPWM);
    analogWrite(motorRightRv, rightRvPWM);
  }
