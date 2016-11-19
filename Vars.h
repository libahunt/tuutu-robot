/**
 * To make good decisions the robot tries to guess what part of track it is on at the moment.
 * For example line gap requires proceeding straight til finding the line again.
 * States have human readable names but are stored as single byte.
 */
#define NORMAL 0
#define GAP 1
#define PRELOOPCROSSING 2
#define LOOPCROSSING 3
#define AFTERLOOPCROSSING 4
#define OBSTACLE 5
#define FLYING 6
#define ALLBLACK 7

byte mode;

#define LEFT 0
#define RIGHT 1
byte loopDirection;

#define HARDLEFT 1
#define SMOOTHLEFT 2
#define STRAIGHT 3
#define SMOOTHRIGHT 4
#define HARDRIGHT 5
byte moveDirection;


/*** Other variables ***********************************************************************************/
int saveCounter = 0; //helper for re-using the history arrays

/*** Storing line sensor data ***/
int sensorReadings[9]; //left to right. Analog readings from sensors.
boolean hasBlack[9];
boolean hasGray[9];
boolean hasLine[17]; //left to right. Whether the line can be detected under one sensor or two neighbouring sensors.
boolean hasLinePrev[17][saveSize];//history of line existence under each sensor or pair of sensors on previous readings
byte noOfLines; //to detect line loop we have to see two lines under sensor at once
byte noOfLinesPrev[saveSize]; //history for it
boolean doubleLine; //true if black-white-black situation detected, but not more than two black areas.

unsigned long interruptTime;
unsigned long lastInterruptTime = 0;
boolean runMotors = false;

/*Obstacle maneuver related*/
int frontDist;
int floorDist;
unsigned long obstacleStart;


/**
 * NORMAL - blue
 * GAP - white
 * PRELOOPCROSSING orange
 * LOOPCROSSING red
 * AFTERLOOPCROSSING purple
 * OBSTACLE 
 * FLYING
 * ALLBLACK
 */


 /*Other*/
int i, j;
int debugCounter = 0;

