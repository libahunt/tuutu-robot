/**
 * Debugging in serial.
 */

void debugSerialPrints() {

  /*Serial print takes lots of time. To avaoid slowing everything down too much let's actually print only after some loops.*/
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

  /*Count loops passed without printing*/
  debugCounter++;
  
}

