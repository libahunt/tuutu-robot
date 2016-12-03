/**
 * Constants that need tweaking during testing.
 */
 
const int hasBlackThres = 150;//analogread value that indicates certain line under the sensor

const float floorOKThres = 4; //over which to assume front of robot is up in the air

const int obstacleDistance = 20; //at which distance measurement to decide that this is obstacle, time to turn, cm

const int fullSpeedPWM = 120; //PWM speed for driving straight and for the outer wheel on turns.
const int slowSpeedPWM = 120; //PWM for slowing down on mountain top (flying mode).
const int hardTurnRvPWM = 120; //PWM speed for the wheel that moves backwards on hard turns.


/**
 * 5 readings per 1cm of movement seems sufficient. 
 * When the average speed of robot is about 10 cm per second, then we want 50 readings in a second.
 * 50 readings per second requires 20ms interval between them.
 */
const int readingInterval = 20-9; //after which time to read line sensors, in milliseconds, minus 9 because 1ms delay is between analogReads

/**
 * Lenght of history arrays should cover about 10cm on previous track.
 * We attempted for 5 readings per cm, so 10cm history is 50 readings long.
 */
const int saveSize = 50; //length of stored history, number of readings

/**
 * After what time to drop back to normal mode when preloop or loop mode have not resolved themselves, ms.
 */
const unsigned long loopTimeout = 1000;

/**
 * Obstacle maneuver timing settings - millisecond duration for each phase from the start of the whole maneuver.
 */
const unsigned long obstacleTimeCoef = 1000;
const unsigned long obstaclePhase1 = 0.8 * obstacleTimeCoef; //turn to leave line
const unsigned long obstaclePhase2 = 1.3 * obstacleTimeCoef + obstaclePhase1; //move away from line
const unsigned long obstaclePhase3 = 0.7 * obstacleTimeCoef + obstaclePhase1 + obstaclePhase2; //turn parallel to line
const unsigned long obstaclePhase4 = 1.1 * obstacleTimeCoef + obstaclePhase1 + obstaclePhase2 + obstaclePhase3; //move parallel to line
const unsigned long obstaclePhase5 = 0.7 * obstacleTimeCoef + obstaclePhase1 + obstaclePhase2 + obstaclePhase3 + obstaclePhase4; //turn back towards the line

/**
 * Tank tower position related.
 */
const int towerUpReading = 800; //potentimeter reading in the upper position
const int towerDownReading = 100;  //potentimeter reading in the lower position
const int towerMotorPWM = 150; //PWM suitable for moving tower motor

