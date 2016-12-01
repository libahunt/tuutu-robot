/***
Linefollowing with obstacles robot operation script.
Arduino MEGA controller.
***/

/**
 * TODO
 * redo turning logic?
 * make preloop detect and save the direction where the new line comes in.
 * make preloop and/or loop get dropped after some reasonable timeout
 * add tower movements functionality
 * 
 */

//#define DEBUG /*comment this line out in production then all DP Serial instructsions are ignored*/
#include "DebugUtils.h"/*leave this in, otherwise you get errors*/

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
Adafruit_NeoPixel turnSignals = Adafruit_NeoPixel(10, PIXELPIN, NEO_GRB + NEO_KHZ800);
#include "SignalColors.h"




void setup() {
  
  /*motors*/
  pinMode(motorLeftFw, OUTPUT);
  pinMode(motorLeftRv, OUTPUT);
  pinMode(motorRightFw, OUTPUT);
  pinMode(motorRightRv, OUTPUT);
  
  /*sensors*/
  pinMode(sensorPins[0], INPUT);
  pinMode(sensorPins[1], INPUT);
  pinMode(sensorPins[2], INPUT);
  pinMode(sensorPins[3], INPUT);
  pinMode(sensorPins[4], INPUT); 
  pinMode(sensorPins[5], INPUT);
  pinMode(sensorPins[6], INPUT);
  pinMode(sensorPins[7], INPUT);
  pinMode(sensorPins[8], INPUT);

  //pinMode(towerPosPot, INPUT);
  //pinMode(towerMotorUp, INPUT);
  //pinMode(towerMotorDown, INPUT);

  attachInterrupt(digitalPinToInterrupt(runToggleButton), toggleRunning, LOW);
  
  #ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Start");
    delay(3000);
  #endif

  turnSignals.begin();
  turnSignals.show();

  mode = NORMAL;
  moveDirection = STRAIGHT;

  /*analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, 0);
  delay(10000);*/

  turnSignals.setPixelColor(0, turnSignals.Color(255, 0, 0));
  turnSignals.setPixelColor(1, turnSignals.Color(0, 255, 0));
  turnSignals.setPixelColor(2, turnSignals.Color(0, 0, 255));
  turnSignals.show();
  delay(5000);
  
  
} // /setup

void loop() {
  
  readSensors();
  saveReadings();

  chooseDirection();
  decideMode();
  
  

  if (runMotors) {
    //moveDir(moveDirection);
    moveMotors(speedPWM, leftSpeedCoef, rightSpeedCoef);
  }
  else {
    //stopMotors();
    moveMotors(0, 0, 0);
  }
  
  
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

    DP(" L:");
    DP(noOfLines);

    DP(" D:");
    DP(moveDirection);
    
    DPL(" ");
    debugCounter = 0;
    
  }
  debugCounter++;

  delay(100);
  //delay(readingInterval);
  
} // /loop


//interrupt service routine for the button
void toggleRunning() {
  // Debouncing interrupt taken from http://forum.arduino.cc/index.php?topic=45000.0
  interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) {
    runMotors = !runMotors;
  }
  lastInterruptTime = interruptTime;
}

    
