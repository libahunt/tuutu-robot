/***
Linefollowing with obstacles robot operation script.
Arduino MEGA controller.
***/

#define DEBUG /*comment this line out in production then all DP Serial instructsions are ignored*/
#include "DebugUtils.h"/*leave this in, otherwise you get errors*/

#include <NewPing.h>
#include <Adafruit_NeoPixel.h>

#include "Layout.h" //Pin connections
#include "Settings.h" //Variables that might need tweaking
#include "Vars.h"

/*** One Ultrasonic distance sensor detects the block shaped obstacle on the track. ***/
NewPing obstacleSonar(TRIGGER_PIN_OBS, ECHO_PIN_OBS, MAX_DISTANCE_OBS);

/*** Second Ultrasonic distance sensor detects when the front of robot hangs over an edge. ***/
NewPing edgeSonar(TRIGGER_PIN_EDGE, ECHO_PIN_EDGE, MAX_DISTANCE_EDGE);

/*** Neopixels are used as fancy "turn signal" lights that give information about the program state. ***/
Adafruit_NeoPixel turnSignals = Adafruit_NeoPixel(4, PIXELPIN, NEO_GRB + NEO_KHZ800);

unsigned long c = turnSignals.Color(0, 0, 0); //Special type for storing NeoPixel color. This variable can be 
                                              // declared only after creating neopixel object
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

//  pinMode(18, INPUT);

  attachInterrupt(digitalPinToInterrupt(18), toggleRunning, LOW);
  
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
 
  delay(3000);

  mode = NORMAL;
  moveDirection = STRAIGHT;

  
} // /setup

void loop() {
  
  readSensors();
  
  decide();
  
 
  saveReadings(); 

  if (runMotors) {
    moveDir(moveDirection);
  }
  else {
    stopMotors();
  }
  
  
  //if (debugCounter == 10) {
  
    for (j=0; j<9; j++) {
      DP(sensorReadings[j]);
      DP(" "); 
    }
    DP("   ");
    DP(runMotors);
    //DP(digitalRead(18));
    DPL(" ");
    /*for (j=0; j<17; j++) {
      DP(hasLine[j]);
      DP(" "); 
    }
    DPL(" ");

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
    
    DPL(" ");*/
    
  //}
  //debugCounter++;
  
  //delay(readingInterval);
  delay(500);
  
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

    
