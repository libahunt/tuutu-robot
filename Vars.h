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
#define TURN90 8
byte mode;

/**
 * Loop direction is saved as byte.
 */
#define LEFT 0
#define RIGHT 1
byte loopDirection;

/**
 * Movements - turn direction, turn steepness or going straight faster or slower are passed as byte.
 */
#define HARDLEFT 1
#define SMOOTHLEFT 2
#define STRAIGHT 3
#define SMOOTHRIGHT 4
#define HARDRIGHT 5
#define SLOWSTRAIGHT 6
#define STOP 7
#define SPINLEFT 8
#define SPINRIGHT 9

/**
 * Line sensors related.
 */
int sensorReadings[9]; //left to right. Analog readings from sensors.
boolean hasLine[9]; //left to right. If the sensor reads below or above the black threshold.
boolean hasLinePrev[saveSize][9];//history of line existence under each sensor on previous readings
byte noOfLines; //to detect line loop we have to see two lines under sensor at once
byte noOfLinesPrev[saveSize]; //history for it
int lineWidth; //how many adjacent sensors showed black - to detect 90 deg turns
int saveCounter = 0; //helper for re-using the history arrays.
byte turn90Direction;

/**
 * Obstacle sensor and maneuver related.
 */
int frontDist; //sensor reading
unsigned long obstacleStart;//for storing time when the maneuver started

/**
 * Detecting hill top where line sensor can not be trusted.
 */
int floorDist; //sensor reading

/**
 * Recovering for erroneus lineloop decisions with timeout.
 */
unsigned long loopStartTime;

/**
 * To do a minimum turn at 90 deg corner before starting to search the line.
 */
unsigned long turn90StartTime;

/**
 * A button changes between drive or stall mode.
 */
boolean haltMotors = true; //current state
unsigned long interruptTime; //for debouncing drive/stall mode button
unsigned long lastInterruptTime = 0; //for debouncing drive/stall mode button

/**
 * Other.
 */
int i, j;
int debugCounter = 0;

