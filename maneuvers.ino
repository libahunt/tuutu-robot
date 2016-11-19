void moveDir(int moveDirection) {
  if (moveDirection == 0) {
    turnLeftHard();
  }
  else if (moveDirection == 1) {
    turnLeft();
  }
  else if (moveDirection == 2) {
    goStraight();
  }
  else if (moveDirection == 3) {
    turnRight();
  }
  else if (moveDirection == 4) {
    turnRightHard();
  }
}
  
void goStraight() { 
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, speedPWM);
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
