/**
 * Interrupt service routine for a button that turns drive motors off, but does not affect sensors.
 * 
 * Sets mode to normal too.
 */

void toggleRunning() {
  interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) {
    haltMotors = !haltMotors;
    mode = NORMAL;
    lastMode = NORMAL;
  }
  lastInterruptTime = interruptTime;
}

