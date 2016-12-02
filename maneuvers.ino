/**
 * Motors are driven based on speed coefficent and maximum PWM value passed into this function.
 * 
 * Coeficent parameters can be negative for reversing movement.
 * Coeficents values don't matter, just their comaprision to each other.
 * On turns maxPWM value is used for the faster turning motor.
 * Because PWM values below a certain point are not able to move the motors very small speeds
 * are set to 0 and slightly higher ones mapped to the scale of working PWM values.
 * minPWM in settings sets the mapping lower point, values less than one third of it are set to 0.
 */

void moveMotors(int maxPWM, float leftSpeedCoef, float rightSpeedCoef) {
  int leftSpeed, rightSpeed, leftFwPWM, leftRvPWM, rightFwPWM, rightRvPWM;
  if (abs(leftSpeedCoef) > abs(rightSpeedCoef)) {
    leftSpeed = maxPWM;
    rightSpeed = map(maxPWM * rightSpeedCoef/leftSpeedCoef, 0,255, minPWM,255);
  }
  else if (abs(leftSpeedCoef) < abs(rightSpeedCoef)) {
    leftSpeed = map(maxPWM * leftSpeedCoef/rightSpeedCoef, 0,255, minPWM,255);
    rightSpeed = maxPWM;
  }
  else {
    leftSpeed = maxPWM;
    rightSpeed = maxPWM;
  }

  if (leftSpeed >= 0) {
    if (leftSpeed < minPWM/3) {
      leftFwPWM = 0;
    }
    else {
      leftFwPWM = map(leftSpeed, 0,maxPWM, minPWM, maxPWM);
    }
    leftRvPWM = 0;
  }
  else {
    leftFwPWM = 0;
    if (leftSpeed > minPWM/-3) {
      leftRvPWM = 0;
    }
    else {
      leftRvPWM = map(-1*leftSpeed, 0,maxPWM, minPWM, maxPWM);
    }
  }
  if (rightSpeed >= 0) {
    if (rightSpeed < minPWM/3) {
      rightFwPWM = 0;
    }
    else {
      rightFwPWM = map(rightSpeed, 0,maxPWM, minPWM, maxPWM);
    }
    rightRvPWM = 0;
  }
  else {
    rightFwPWM = 0;
    if (rightSpeed > minPWM/-3) {
      rightRvPWM = 0;
    }
    else {
      rightRvPWM = map(-1*rightSpeed, 0,maxPWM, minPWM, maxPWM);
    } 
  }

  analogWrite(motorLeftFw, leftFwPWM);
  analogWrite(motorLeftRv, leftRvPWM);
  analogWrite(motorRightFw, rightFwPWM);
  analogWrite(motorRightRv, rightRvPWM);
    
}



/**
 * Follows one line out of two.
 * 
 * On loop crossings the robot has to follow the line on the side where it previously saw new line coming in.
 */

void followOneLine(byte chosenDirection) {
  if (chosenDirection == LEFT) {

  }
  
}
  
