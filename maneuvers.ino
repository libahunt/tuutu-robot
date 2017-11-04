/**
 * Moving motors.
 * 
 * If the global variable haltMotors is set motors do not move.
 * Direction and in case of straight also speed of movement is passed as parameter.
 */
void moveMotors(byte moveDirectionMode) {
  
  if (!haltMotors) {
    
    switch (moveDirectionMode) {
    
      case HARDLEFT:
        analogWrite(motorLeftFw, 0);
        analogWrite(motorLeftRv, hardTurnRvPWM);
        analogWrite(motorRightFw, hardTurnFwPWM);
        analogWrite(motorRightRv, 0);
        break;
        
      case SMOOTHLEFT:
        analogWrite(motorLeftFw, 0);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, fullSpeedPWM);
        analogWrite(motorRightRv, 0);
        break;

      case SPINLEFT :
        analogWrite(motorLeftFw, 0);
        analogWrite(motorLeftRv, slowSpeedPWM);
        analogWrite(motorRightFw, slowSpeedPWM);
        analogWrite(motorRightRv, 0);
        break;
        
      case STRAIGHT:
        analogWrite(motorLeftFw, fullSpeedPWM);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, fullSpeedPWM);
        analogWrite(motorRightRv, 0);
        break;
        
      case SMOOTHRIGHT:
        analogWrite(motorLeftFw, fullSpeedPWM);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, 0);
        analogWrite(motorRightRv, 0);
        break;
        
      case HARDRIGHT:
        analogWrite(motorLeftFw, hardTurnFwPWM);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, 0);
        analogWrite(motorRightRv, hardTurnRvPWM);
        break;

      case SPINRIGHT: 
        analogWrite(motorLeftFw, slowSpeedPWM);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, 0);
        analogWrite(motorRightRv, slowSpeedPWM);
        break;
        
      case SLOWSTRAIGHT:
        analogWrite(motorLeftFw, slowSpeedPWM);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, slowSpeedPWM);
        analogWrite(motorRightRv, 0);
        break;

      default: //STOP
        analogWrite(motorLeftFw, 0);
        analogWrite(motorLeftRv, 0);
        analogWrite(motorRightFw, 0);
        analogWrite(motorRightRv, 0);
        break;
    }
  }
  
  else { 
    /*haltMotors is set to true, stop motors.*/
    analogWrite(motorLeftFw, 0);
    analogWrite(motorLeftRv, 0);
    analogWrite(motorRightFw, 0);
    analogWrite(motorRightRv, 0);
  }
  
}
  
