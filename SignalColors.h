/**
 * Turnsignal colors
 * NORMAL - blue
 * GAP - white
 * PRELOOPCROSSING orange
 * LOOPCROSSING red
 * AFTERLOOPCROSSING purple
 * OBSTACLE yellow
 * FLYING red
 * ALLBLACK green
*/

unsigned long c = turnSignals.Color(0, 0, 0); //Special type for storing NeoPixel color. This variable can be 
                                              // declared only after creating neopixel object
                                              
unsigned long colorNormal = turnSignals.Color(0, 0, 255);   //blue
unsigned long colorNormalDim = turnSignals.Color(0, 0, 50);   
unsigned long colorGap = turnSignals.Color(90, 90, 90);      //white
//no line, no need for two colors
unsigned long colorPreloop = turnSignals.Color(200, 55, 0);  //orange
unsigned long colorPreloopDim = turnSignals.Color(40, 10, 0);  
unsigned long colorLoop = turnSignals.Color(255, 0, 0);     //red
unsigned long colorLoopDim = turnSignals.Color(50, 0, 0);     
unsigned long colorAfterloop = turnSignals.Color(127, 0, 127);//purple
unsigned long colorAfterloopDim = turnSignals.Color(25, 0, 25);
unsigned long colorObstacle = turnSignals.Color(127, 127, 0); //yellow
unsigned long colorObstacleDim = turnSignals.Color(25, 25, 0); 
unsigned long colorFlying = turnSignals.Color(230, 0, 20);   //purplish red
unsigned long colorFlyingDim = turnSignals.Color(46, 0, 4);  
unsigned long colorAllblack = turnSignals.Color(0, 255, 0); //green
unsigned long colorAllblackDim = turnSignals.Color(0, 50, 0); 

unsigned long colorOff = turnSignals.Color(0, 0, 0);
