/**
 * Layout - physical pin connections.
 */

/*Neopixel RHB LED strip is used as visual feedback indicator for the states of the robot and line readings.*/
#define PIXELPIN 7

/*One Ultrasonic distance sensor detects the block shaped obstacle on the track.*/
#define TRIGGER_PIN_OBS  8
#define ECHO_PIN_OBS     9

/*Second Ultrasonic distance sensor detects when the front of robot hangs over an edge.*/
#define TRIGGER_PIN_EDGE  12
#define ECHO_PIN_EDGE     11

/*Drive motors H-bridge connections.*/
const int motorLeftFw = 5;
const int motorLeftRv = 4;
const int motorRightFw = 3;
const int motorRightRv = 2;

/*Line sensors connections.*/
const int sensorPins[] = {A7, A6, A5, A4, A3, A8, A0, A1, A2}; //left to right

/*Interrupt button to toggle if motors should run or not. Has to be interrupt-capable.*/
const int runToggleButton = 18;

