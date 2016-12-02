/**
 * Linefollowing with obstacles - robot operation script.
 * 
 * For Arduino MEGA controller.
 * 
 * By Anna Jõgi a.k.a Libahunt Dec 30 2016. Version 0.1.
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 */


/**
 * TODO:
 * TEST: -turning logic might need revision about too low PWM-s
 * make afterloop follow the right line
 * make obstacle maneuver work
 * add tower movements functionality
 * 
 */

#define DEBUG /*Comment this line out in production then all DP Serial instructions are ignored*/
#include "DebugUtils.h"/*Leave this in, otherwise you get errors.*/

#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#include "Layout.h" //Pin connections
#include "Settings.h" //Variables that might need tweaking
#include "Vars.h" //Other variable declarations

/*** One Ultrasonic distance sensor detects the block shaped obstacle on the track. ***/
NewPing obstacleSonar(TRIGGER_PIN_OBS, ECHO_PIN_OBS, MAX_DISTANCE_OBS);

/*** Second Ultrasonic distance sensor detects when the front of robot hangs over an edge. ***/
NewPing edgeSonar(TRIGGER_PIN_EDGE, ECHO_PIN_EDGE, MAX_DISTANCE_EDGE);

/*** Neopixels are used as fancy "turn signal" lights that give information about the program state. ***/
Adafruit_NeoPixel signalLights = Adafruit_NeoPixel(10, PIXELPIN, NEO_GRB + NEO_KHZ800);
#include "SignalColors.h"




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

  attachInterrupt(digitalPinToInterrupt(runToggleButton), toggleRunning, LOW);
  
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Started");
  #endif

  /*Turn off previous state in RGB LEDs.*/
  signalLights.begin();
  signalLights.show();

  mode = NORMAL;
  lastMode = NORMAL;
  
}



void loop() {

  /*Take measurements and save them.*/
  readSensors();
  saveReadings();

  /*Derive mode from sensor readings.*/
  decideMode();

  /*Get line direction*/
  moveDirectionForLine();

  /*Behaviours in different modes.*/
  switch (mode) {
    case NORMAL:
      moveMotors(lineDirection);
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
      Hoping this is not erroneus reading and the two lines will gather into one soon. */
      moveMotors(lineDirection);
      break;
      
    case LOOPCROSSING:
      moveMotors(lineDirection);
      break;
      
    case AFTERLOOPCROSSING:
      /*Follow the line on the side that previously saw new line coming in. Full speed.*/
      /*TODO: this somehow does not compile
       * byte selectedLineDirection = moveDirectionForOneLine(loopDirection);
      moveMotors(selectedLineDirection);*/
      break;

    case OBSTACLE:
      /*Passing by obstacle is a simple time based maneuver that does not need sensor readings. Will just do these things in sequence.*/
      /*turnRightHard();
      delay(obstaclePhase1);
      goStraight();
      delay(obstaclePhase2);
      turnLeftHard();
      delay(obstaclePhase3);
      goStraight();
      delay(obstaclePhase4);
      turnLeftHard();
      delay(obstaclePhase5);
      mode = GAP; //in gap mode goes straight until finding line again
      moveDirection = STRAIGHT;    */  
      
      /*temp*/
      delay(500);
      mode = NORMAL;
      break;
  }


  /* Show mode and line sensor readings status on a strip of RGB LEDs*/
  signalLightsShow();
  


  
  #ifdef DEBUG
    if (debugCounter == 25) {
    
      for (j=0; j<9; j++) {
        DP(sensorReadings[j]);
        DP(" "); 
      }
      for (j=0; j<9; j++) {
        DP(hasLine[j]);
      }
      DP(" ");
  
      DP("Front: ");
      DP(frontDist);
  
      DP(" \t Floor: ");
      DP(floorDist);
      DP(" \t");
      
      if (mode == NORMAL) {
        DP("NORMAL");
      }
      else if (mode == GAP) {
        DP("GAP"); 
      }
      else if (mode == PRELOOPCROSSING) {
        DP("PRELOOP");
      }
      else if (mode == LOOPCROSSING) {
        DP("LOOP");
      }
      else if (mode == AFTERLOOPCROSSING) {
        DP("AFTERLOOP");
      }
      else if(mode == OBSTACLE) {
        DP("OBSTACLE");
      }  
      else if(mode == FLYING) {
        DP("FLYING");
      }  
      else if(mode == ALLBLACK) {
        DP("ALLBLACK");
      }
  
      DP(" Lines:");
      DP(noOfLines);
  

      DP(" tp");
      DP(analogRead(towerPosPot));
      
      DPL(" ");
    
      debugCounter = 0;
      
    }
    debugCounter++;

  #endif

  /*Wait a little before measuring and driving again.*/
  delay(readingInterval);
  
}
    
