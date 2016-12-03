/**
 * Constants that need tweaking during testing.
 */
 
const int hasBlackThres = 200;//analogread value that indicates certain line under the sensor

const float floorOKThres = 10; //over which to assume front of robot is up in the air

const int obstacleDistance = 15; //at which distance measurement to decide that this is obstacle, time to turn, cm

const int fullSpeedPWM = 150; //PWM speed for driving straight and for the outer wheel on smooth turns.
const int slowSpeedPWM = 130; //PWM for slowing down on mountain top (flying mode).
const int hardTurnRvPWM = 255; //PWM speed for the wheel that moves backwards on hard turns.
const int hardTurnFwPWM = 130; //PWM speed for the wheel that moves forard on hard turns.


/**
 * 5 readings per 1cm of movement seems sufficient. 
 * When the average speed of robot is about 10 cm per second, then we want 50 readings in a second.
 * 50 readings per second requires 20ms interval between them.
 */
const int readingInterval = 9-9; //after which time to read line sensors, in milliseconds, minus 9 because 1ms delay is between analogReads

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
const unsigned long obstacleTimeCoef = 1200;
const unsigned long obstaclePhase1 = 0.8 * obstacleTimeCoef; //turn to leave line
const unsigned long obstaclePhase2 = 0.9 * obstacleTimeCoef; //move away from line
const unsigned long obstaclePhase3 = 0.7 * obstacleTimeCoef; //turn parallel to line
const unsigned long obstaclePhase4 = 1.1 * obstacleTimeCoef; //move parallel to line
const unsigned long obstaclePhase5 = 0.8 * obstacleTimeCoef; //turn back towards the line


/**
 * Ultrasonic distance sensors max distance settings.
 */
#define MAX_DISTANCE_OBS 100
#define MAX_DISTANCE_EDGE 100

