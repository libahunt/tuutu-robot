
void signalLights(byte mode) {
  unsigned long color;
  unsigned long colorDim;
  switch (mode) {
    case NORMAL:
      color=colorNormal;
      colorDim=colorNormalDim;
      break;
    case GAP:
      color=colorGap;
      colorDim=colorGap;
      break;
    case PRELOOPCROSSING:
      color=colorPreloop;
      colorDim=colorPreloopDim;
      break;
    case LOOPCROSSING:
      color=colorLoop;
      colorDim=colorLoopDim;
      break;
    case AFTERLOOPCROSSING:
      color=colorAfterloop;
      colorDim=colorAfterloopDim;
      break;
    case OBSTACLE:
      color=colorObstacle;
      colorDim=colorObstacleDim;
      break;
    case FLYING:
      color=colorFlying;
      colorDim=colorFlyingDim;
      break;
    default: // ALLBLACK
      color=colorAllblack;
      colorDim=colorAllblackDim;
  }

  for(i=0; i<9; i++) {
      if (hasLine[i]) {
        turnSignals.setPixelColor(i, color);
      }
      else {
        turnSignals.setPixelColor(i, colorDim);
      }
    }
    turnSignals.show();
}



/**
 * Set up and interrupt that checks the operation mode and line position
 * and sets signal lights accordingly.
 */
/*
void setTimerInterrupt() {
  //from http://www.instructables.com/id/Arduino-Timer-Interrupts/?ALLSTEPS
  cli();//stop interrupts
  //set timer0 interrupt at 50Hz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 50hz increments
  OCR0A = 1249;// = (16*10^6) / (50*256) - 1 (must be <65536 for timer 0) 256  1249

  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS02  bit for 256 prescaler
  TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  sei();//enable interrupts
}

ISR(TIMER0_COMPA_vect){

}*/


