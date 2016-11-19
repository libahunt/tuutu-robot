
int hasBlackThres = 150;//analogread value that indicates certain line under the sensor
int hasGrayThres = 80;//analogread value that indicates possible line under the sensor

float floorOKThres = 4; //over which to assume front of robot is up in the air

/**
 * 5 readings per 1cm of movement seems sufficient. 
 * When the average speed of robot is about 10 cm per second, then we want 50 readings in a second.
 * 50 readings per second requires 20ms interval between them.
 */
int readingInterval = 20; //after which time to read line sensors, in milliseconds

int speedPWM = 120; //PWM speed for driving straight and for the outer wheel on turns
int hardTurnPWM = speedPWM * 0.75;

/*obstacle maneuver timing settings - millisecond duration for each phase*/
unsigned long obstacleTimeCoef = 1000;
unsigned long obstaclePhase1 = 0.8 * obstacleTimeCoef; //turn to leave line
unsigned long obstaclePhase2 = 1.3 * obstacleTimeCoef;; //move away from line
unsigned long obstaclePhase3 = 0.7 * obstacleTimeCoef;; //turn parallel to line
unsigned long obstaclePhase4 = 1.1 * obstacleTimeCoef;; //move parallel to line
unsigned long obstaclePhase5 = 0.7 * obstacleTimeCoef;; //turn back towards the line

int obstacleDistance = 20; //at which distance measurement to decide that this is obstacle, time to turn, cm

/**
 * Lenght of history arrays should cover about 10cm on previous track.
 * We attempted for 5 readings per cm, so 10cm history is 50 readings long.
 */
const int saveSize = 50; //length of stored history, number of readings




