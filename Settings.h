/**
 * Variables that need tweaking during testing.
 */
 
int hasBlackThres = 150;//analogread value that indicates certain line under the sensor

float floorOKThres = 4; //over which to assume front of robot is up in the air

int obstacleDistance = 20; //at which distance measurement to decide that this is obstacle, time to turn, cm

int fullSpeedPWM = 120; //PWM speed for driving straight and for the outer wheel on turns
int slowSpeedPWM = 120; //PWM for slowing down on mountain top (flying mode).


/**
 * 5 readings per 1cm of movement seems sufficient. 
 * When the average speed of robot is about 10 cm per second, then we want 50 readings in a second.
 * 50 readings per second requires 20ms interval between them.
 */
int readingInterval = 20-9; //after which time to read line sensors, in milliseconds, minus 9 because 1ms delay is between analogReads

/**
 * Lenght of history arrays should cover about 10cm on previous track.
 * We attempted for 5 readings per cm, so 10cm history is 50 readings long.
 */
const int saveSize = 50; //length of stored history, number of readings

/**
 * After what time to drop back to normal mode when preloop or loop mode have not resolved themselves, ms.
 */
unsigned long loopTimeout = 1000;

/**
 * Obstacle maneuver timing settings - millisecond duration for each phase.
 */
unsigned long obstacleTimeCoef = 1000;
unsigned long obstaclePhase1 = 0.8 * obstacleTimeCoef; //turn to leave line
unsigned long obstaclePhase2 = 1.3 * obstacleTimeCoef;; //move away from line
unsigned long obstaclePhase3 = 0.7 * obstacleTimeCoef;; //turn parallel to line
unsigned long obstaclePhase4 = 1.1 * obstacleTimeCoef;; //move parallel to line
unsigned long obstaclePhase5 = 0.7 * obstacleTimeCoef;; //turn back towards the line

/**
 * Tank tower position related.
 */
int towerUpReading = 800; //potentimeter reading in the upper position
int towerDownReading = 100;  //potentimeter reading in the lower position
int towerMotorPWM = 150; //PWM suitable for moving tower motor




