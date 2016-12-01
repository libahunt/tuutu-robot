/**
 * Motors are driven based on speed coefficent and maximum PWM value passed into this function.
 * 
 * Coeficent parameters can be negative for reversing movement.
 * Coeficents values don't matter, just their comaprision to each other.
 * On turns maxPWM value is used for the faster turning motor.
 */

void moveMotors(int maxPWM, float leftSpeedCoef, float rightSpeedCoef) {
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
  
