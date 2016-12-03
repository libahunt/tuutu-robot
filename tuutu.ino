/**
 * Linefollowing with obstacles - robot operation script.
 * 
 * For Arduino MEGA controller.
 * 
 * By Anna Jõgi a.k.a Libahunt Dec 3 2016. Version 0.1.
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 */


/**
 * TODO:
 * add tower movements functionality
 * 
 */

//#define DEBUG /*Comment this line out in production then all DP Serial instructions are ignored.*/
#include "DebugUtils.h"/*Leave this in, otherwise you get errors.*/

#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#include "Layout.h" //Pin connections
#include "Settings.h" //Variables that might need tweaking
#include "Vars.h" //Other variable declarations

/*One Ultrasonic distance sensor detects the block shaped obstacle on the track.*/
NewPing obstacleSonar(TRIGGER_PIN_OBS, ECHO_PIN_OBS, MAX_DISTANCE_OBS);

/*Second Ultrasonic distance sensor detects when the front of robot hangs over an edge.*/
NewPing edgeSonar(TRIGGER_PIN_EDGE, ECHO_PIN_EDGE, MAX_DISTANCE_EDGE);

/*Neopixel RGB LED strip is used as visual feedback indicator for the states of the robot and line readings.*/
Adafruit_NeoPixel signalLights = Adafruit_NeoPixel(9, PIXELPIN, NEO_GRB + NEO_KHZ800);
#include "SignalColors.h" //State color definitions



void setup() {
  
  /*Motors.*/
  pinMode(motorLeftFw, OUTPUT);
  pinMode(motorLeftRv, OUTPUT);
  pinMode(motorRightFw, OUTPUT);
  pinMode(motorRightRv, OUTPUT);
  
  /*Sensors.*/
  for (i=0; i<9; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  //pinMode(towerPosPot, INPUT);
  //pinMode(towerMotorUp, INPUT);
  //pinMode(towerMotorDown, INPUT);

  /*Button that halts motors but keeps sensors running.*/
  attachInterrupt(digitalPinToInterrupt(runToggleButton), toggleRunning, LOW);
  
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

  /*Turn off previous state in RGB LEDs.*/
  signalLights.begin();
  signalLights.show();

  /*Start in "normal" mode.*/
  mode = NORMAL;
  
}



void loop() {

  /*Obstacle maneuver is a special case that does not need readings, it's time based.*/
  if (mode != OBSTACLE) {

    /*Take measurements and save them.*/
    readSensors();
    saveReadings();

    /*Derive mode from sensor readings.*/
    decideMode();
    
  }
  

  /*Behaviours in different modes.*/
  switch (mode) {
    case NORMAL:
      moveMotors(getLineDirection());
      break;
      
    case GAP:
      moveMotors(STRAIGHT);
      break;
      
    case ALLBLACK:
      moveMotors(STRAIGHT);
      break;
      
    case FLYING:
      moveMotors(SLOWSTRAIGHT);
      break;
      
    case PRELOOPCROSSING:
      /* Decide from line sensor readings, full speed. 
      The two lines should gather into one soon.*/
      moveMotors(getLineDirection());
      break;
      
    case LOOPCROSSING:
      /*When entering this mode saved data is analyzed to detect which side the new line came in.*/
      moveMotors(getLineDirection());
      break;
      
    case AFTERLOOPCROSSING:
      /*Follow the line on the side that previously saw new line coming in. Full speed.*/
      moveMotors(moveDirectionForOneLine(loopDirection));
      break;

    case OBSTACLE:
      /*Passing by obstacle is a simple time based maneuver. Will just do these things in sequence.*/
      unsigned long currentTime = millis();
      if (currentTime <= obstacleStart + obstaclePhase1) {
        moveMotors(HARDLEFT);
      }
      else if (currentTime <= obstacleStart + obstaclePhase2) {
        moveMotors(STRAIGHT);
      }
      else if (currentTime <= obstacleStart + obstaclePhase3) {
        moveMotors(HARDRIGHT);
      }
      else if (currentTime <= obstacleStart + obstaclePhase4) {
        moveMotors(STRAIGHT);
      }
      else if (currentTime <= obstacleStart + obstaclePhase5) {
        moveMotors(HARDRIGHT);
      }
      /*Turned back towards the line, exit obstacle mode into gap mode.*/
      else {
        mode = GAP;
      }
      break;
  }


  /* Show mode and line sensor readings status on a strip of RGB LEDs*/
  signalLightsShow();

  
  #ifdef DEBUG
    debugSerialPrints();
  #endif


  /*Wait a little before measuring and deciding again.*/
  delay(readingInterval);
  
}
    
