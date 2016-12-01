/**
 * Layout - physical pin connections.
 */

/*** Neopixels are used as fancy "turn signal" lights that give information about the program state. ***/
#define PIXELPIN 7

/*** One Ultrasonic distance sensor detects the block shaped obstacle on the track. ***/
#define TRIGGER_PIN_OBS  8
#define ECHO_PIN_OBS     9
#define MAX_DISTANCE_OBS 200

/*** Second Ultrasonic distance sensor detects when the front of robot hangs over an edge. ***/
#define TRIGGER_PIN_EDGE  12
#define ECHO_PIN_EDGE     11
#define MAX_DISTANCE_EDGE 100

/*** Drive motors H-bridge connections. ***/
const int motorLeftFw = 5;
const int motorLeftRv = 4;
const int motorRightFw = 3;
const int motorRightRv = 2;

/*** Line sensors connections. ***/
const int sensorPins[] = {A7, A6, A5, A4, A3, A8, A0, A1, A2}; //left to right

/*** Tank tower is moved by DC motor (H-bridge) and position tracked with a potentiometer. ***/
const int towerPosPot = A11;
const int towerMotorUp = 14;
const int towerMotorDown = 15;

/*** Interrupt button to toggle if motors should run or not. Has to be interrupt-capable. ***/
const int runToggleButton = 18;

