/**
 * Signal lights color definitions.
*/

unsigned long c = signalLights.Color(0, 0, 0); //Special type for storing NeoPixel color. This variable can be 
                                              // declared only after creating neopixel object
                                              
unsigned long colorNormal = signalLights.Color(0, 255, 0);   //green
unsigned long colorNormalDim = signalLights.Color(0, 25, 0);   
unsigned long colorGap = signalLights.Color(85, 85, 85);      //white
unsigned long colorGapDim = signalLights.Color(9, 9, 9);    
unsigned long colorPreloop = signalLights.Color(127, 0, 127);//purple
unsigned long colorPreloopDim = signalLights.Color(12, 0, 12);
unsigned long colorLoop = signalLights.Color(0, 0, 255);     //blue
unsigned long colorLoopDim = signalLights.Color(0, 0, 25);     
unsigned long colorAfterloop = signalLights.Color(0, 125, 125);  //bluish green
unsigned long colorAfterloopDim = signalLights.Color(0, 12, 12);
unsigned long colorObstacle = signalLights.Color(127, 127, 0); //yellow
unsigned long colorObstacleDim = signalLights.Color(12, 12, 0); 
unsigned long colorFlying = signalLights.Color(255, 0, 0);   //red
unsigned long colorFlyingDim = signalLights.Color(25, 0, 0);  
unsigned long colorAllblack = signalLights.Color(85, 85, 85); //white
unsigned long colorAllblackDim = signalLights.Color(9, 9, 9); 

unsigned long colorOff = signalLights.Color(0, 0, 0);

