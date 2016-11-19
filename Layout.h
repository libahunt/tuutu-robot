/*** Layout - physical connections ***/

/*** Neopixels are used as fancy "turn signal" lights that give information about the program state. ***/
#define PIXELPIN 8 //NeoPixels control wire.

/*** One Ultrasonic distance sensor detects the block shaped obstacle on the track. ***/
#define TRIGGER_PIN_OBS  2
#define ECHO_PIN_OBS     3
#define MAX_DISTANCE_OBS 200

/*** Second Ultrasonic distance sensor detects when the front of robot hangs over an edge. ***/
#define TRIGGER_PIN_EDGE  12
#define ECHO_PIN_EDGE     11
#define MAX_DISTANCE_EDGE 100

const int motorLeftFw = 5;
const int motorLeftRv = 4;
const int motorRightFw = 3;
const int motorRightRv = 2;

const int sensorPins[] = {A7, A6, A5, A4, A3, A2, A1, A0, A8}; //left to right

const int towerPosPot = A9;

/*Pin 18 is for interrupt button to toggle if motors should run or not*/


