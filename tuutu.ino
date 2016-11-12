/***
Linefollower robot operation script
***/

//#define DEBUG /*comment this line out in production then all DP Serial instructsions are ignored*/
#include "DebugUtils.h"/*leave this in, otherwise you get errors*/


#include <NewPing.h>

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     2  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define NORMAL 0
#define GAP 1
#define PRELOOPCROSSING 2
#define LOOPCROSSING 3
#define AFTERLOOPCROSSING 4
#define OBSTACLE 5
byte mode = NORMAL;

#define LEFT 0
#define RIGHT 1
byte loopDirection;

/*Layout - physical connections*/
const int motorLeftFw = 10;
const int motorLeftRv = 9;
const int motorRightFw = 6;
const int motorRightRv = 5;

const int sensorPins[] = {A0, A1, A2, A3, A4}; //left to right

/*storing line sensor data*/
int sensorReadings[5]; //left to right
boolean hasLine[5]; //left to right
const int saveSize = 50;
boolean hasLinePrev[5][saveSize];//lenght of array should cover about 10cm of previous track
boolean hadBlack[5];
byte noOfLines;
byte noOfLinesPrev[saveSize];
int saveCounter = 0;

/*obstacle maneuver related*/
int frontDist;
unsigned long obstacleStart;

/*other*/
int i, j;
boolean ledState = LOW;
int debugCounter = 0;


/**** SETTINGS ******************************************************************************************/

int hasLineThres = 60;//analogread value that indicates line under the sensor
int readingInterval = 20; //after which time to read line sensors, in milliseconds
//ideal would be around 5 readings per 1 cm of movement

int speedPWM = 255; //PWM speed for driving straight and for the outer wheel on turns
int hardTurnPWM = speedPWM * 0.75;

/*obstacle maneuver timing settings - millisecond duration for each phase*/
unsigned long obstaclePhase1 = 800; //turn to leave line
unsigned long obstaclePhase2 = 1300; //move away from line
unsigned long obstaclePhase3 = 700; //turn parallel to line
unsigned long obstaclePhase4 = 1100; //move parallel to line
unsigned long obstaclePhase5 = 700; //turn back towards the line

int obstacleDistance = 20; //at which distance measurement to decide that this is obstacle, time to turn, cm




void setup() {
  
  
  /*motors*/
  pinMode(motorLeftFw, OUTPUT);
  pinMode(motorLeftRv, OUTPUT);
  pinMode(motorRightFw, OUTPUT);
  pinMode(motorRightRv, OUTPUT);
  
  pinMode(13, OUTPUT);
  
  /*sensors*/
  pinMode(sensorPins[0], INPUT);
  pinMode(sensorPins[1], INPUT);
  pinMode(sensorPins[2], INPUT);
  pinMode(sensorPins[3], INPUT);
  pinMode(sensorPins[4], INPUT); 
  
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
 
  delay(3000);
   
  
} // /setup

void loop() {
  
  readSensors();
  
  
  /*** PING reads object ahead ***/
  
  if (frontDist < obstacleDistance && frontDist > 10) {
    //stopMotors();
    mode = OBSTACLE;
    //obstacleStart = millis();
  }
 
  if (mode == OBSTACLE) {
    digitalWrite(13, 0);   
    /*pass by obstacle maneuver
    while (obstacleStart + obstaclePhase1 < millis()) {
      turnRight();
    }
    obstacleStart = millis();
    while (obstacleStart + obstaclePhase2 < millis()) {
      goStraight();
    }
    obstacleStart = millis();
    while (obstacleStart + obstaclePhase3 < millis()) {
      turnLeft();
    }
    obstacleStart = millis();
    while (obstacleStart + obstaclePhase4 < millis()) {
      goStraight();
    }
    obstacleStart = millis();
    while (obstacleStart + obstaclePhase5 < millis()) {
      turnLeft();
    }
    */
    turnRightHard();
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
  }
  
  
  /*** Outermost sensors read black ***/
  
  else if (mode == NORMAL && hasLine[0] && hasLine[4]) {//both black
  digitalWrite(13, 0);
    goStraight();//assume start-finish markings, ignore
  }
  
  else if (mode == NORMAL && hasLine[0]) {
    digitalWrite(13, 0);
    if (!hasLine[1] && (hasLine[2] || hasLine[3]) ) {//black-white-black situation
      mode = PRELOOPCROSSING;//assume loop
      loopDirection = LEFT;
    }
    else {//assume big offset or sharp turn
      turnLeftHard();
    }
  }
  else if (mode == NORMAL && hasLine[4]) {
    digitalWrite(13, 0);
    if (!hasLine[3] && (hasLine[2] || hasLine[1]) ) {//black-white-black situation
      mode = PRELOOPCROSSING;//assume loop
      loopDirection = RIGHT;
    }
    else {//assume big offset or sharp turn
      turnRightHard(); 
    }    
  }
  
  
  /*** One line detected ***/
  
  else if (mode == NORMAL && noOfLines == 1) {
    digitalWrite(13, 0);
    if (hasLine[1]) {
      turnLeft();
    }
    else if (hasLine[3]) {
      turnRight();
    }
    else {//center sensor has line
      goStraight();  
    }
  }
  
  /*** No line detected ***/
  
  else if (mode == NORMAL && noOfLines == 0) {
    digitalWrite(13, 0);
    if (hadBlack[0]) {
      turnLeftHard();
    }
    else if (hadBlack[4]) {
      turnRightHard();
    }
    else {
      goStraight();
    }
    //analyze previous ~1cm measurements
    /*int hasLineStats = 0;
    for (i=0; i<saveSize/10; i++) {
      int savePosition;
      if (saveCounter - i >= 0) {
        savePosition = saveCounter - i;
      }
      else {
        savePosition = saveSize + saveCounter - i;
      }
      if (noOfLinesPrev[savePosition] > 0) {
        hasLineStats++;
      }
    }
    if (float(hasLineStats)*10/saveSize < 0.5) {//too few proof of line existance
      mode = GAP;
      goStraight(); 
    }
    else {//just go straight and postpone decisions ...
      goStraight();  
    }*/
    
  }

  
  else if (mode == GAP && noOfLines > 0) {//found line again
    
    mode = NORMAL;
    if (noOfLines > 0 && noOfLines >=2) {
      if (hasLine[0]) {
        turnLeftHard();
      }
      else if (hasLine[1]) {
        turnLeft(); 
      }
      else if (hasLine[3]) {
        turnRight();
      }
      else if (hasLine[4]) {
        turnRightHard(); 
      }
      else {//center sensor has line
        goStraight();  
      }
    }
    else {//too many lines, assume end of obstacle routine
      turnRight();
    }
  }
  
  else if (mode == GAP) {//no lines
    digitalWrite(13, 0);
    goStraight();
  }
  
  else if (mode == PRELOOPCROSSING) {
    if (noOfLines == 1) {
      mode = LOOPCROSSING;
    }
    goStraight();
    digitalWrite(13, 1);
  }
  
  else if (mode == LOOPCROSSING) {
    if (noOfLines > 1) {
      if (loopDirection == LEFT) {//need to choose left direction
        if (hasLine[0] || hasLine[1]) { //some turn needed
          turnLeft();
        }
        else {
           goStraight();
        }
      }
      else {//need to choose right direction
        if (hasLine[3] || hasLine[4]) { //some turn needed
          turnRight();
        }
        else {
          goStraight();
        }
      }
      mode = AFTERLOOPCROSSING;
      
    }
    else {//second line is not visible yet, follow the track
      if (hasLine[1] || hasLine[0]) {
        turnLeft();
      }
      else if (hasLine[3] || hasLine[4]) {
        turnRight();
      }
      else {//center sensor has line
        goStraight();  
      }
    }
    digitalWrite(13, 0);
  }
  
  else if (mode == AFTERLOOPCROSSING) {
    if (noOfLines > 1) {
      if (loopDirection == LEFT) {//need to choose left direction
        if (hasLine[0] || hasLine[1]) { //some turn needed
          turnLeft();
          delay(300);
        }
        else {
           goStraight();
        }
      }
      else {//need to choose right direction
        if (hasLine[3] || hasLine[4]) { //some turn needed
          turnRight();
          delay(300);
        }
        else {
          goStraight();
        }
      }
    }
    else {//second line is not visible any more
      mode = NORMAL;
      if (hasLine[1] || hasLine[0]) {
        turnLeft();
      }
      else if (hasLine[3] || hasLine[4]) {
        turnRight();
      }
      else {//center sensor has line
        goStraight();  
      }
    }
    digitalWrite(13, 1);
  }
  
  /*save line existence states*/
  for (i=0; i<5; i++) {
    hasLinePrev[i][saveCounter] = hasLine[i];
    if (noOfLines>0) {//save onöy if line was detected
      hadBlack[i] = hasLine[i]; 
    }
    noOfLinesPrev[saveCounter] = noOfLines;
  }
  saveCounter++;
  if (saveCounter == saveSize) {
    saveCounter = 0;
  } 
   
     
  
  
  
  //if (debugCounter == 10) {
  
    for (j=0; j<5; j++) {
      DP(hasLine[j]);
      DP(" "); 
    }
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
    
    DPL(" ");
    
  //}
  debugCounter++;
  
  delay(readingInterval);
  
} // /loop


void readSensors() {
  
  noOfLines = 0;
  for (i=0; i<5; i++) {
    sensorReadings[i] = analogRead(sensorPins[i]); 
    if (sensorReadings[i] > hasLineThres) {
      hasLine[i] = true;
      noOfLines++;
    }
    else {
      hasLine[i] = false;
    }
      
    delay(1);
  }
  
  frontDist = sonar.ping_cm();
  
} // /readSensors


  
void goStraight() { 
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, speedPWM);
  analogWrite(motorLeftRv, 0);
}

void turnLeft() {
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, 0);
}

void turnRight() {
  analogWrite(motorRightFw, 0);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, speedPWM);
  analogWrite(motorLeftRv, 0);
}

void turnLeftHard() {
  analogWrite(motorRightFw, speedPWM);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, hardTurnPWM);
}

void turnRightHard() {
  analogWrite(motorRightFw, 0);
  analogWrite(motorRightRv, hardTurnPWM);
  analogWrite(motorLeftFw, speedPWM);
  analogWrite(motorLeftRv, 0);
}

void stopMotors() {
  analogWrite(motorRightFw, 0);
  analogWrite(motorRightRv, 0);
  analogWrite(motorLeftFw, 0);
  analogWrite(motorLeftRv, 0);
}
    
