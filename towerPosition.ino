
void towerUp() {
  while (analogRead(towerPosPot) < towerUpReading) {
    analogWrite(towerMotorUp,towerMotorPWM);
    delay(10);
  }
  analogWrite(towerMotorUp,0);
}

void towerDown() {
  while (analogRead(towerPosPot) > towerDownReading) {
    analogWrite(towerMotorDown,towerMotorPWM);
    delay(10);
  }
  analogWrite(towerMotorDown,0);
}

