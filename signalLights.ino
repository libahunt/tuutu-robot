
void signalLightsShow() {
  unsigned long color;
  unsigned long colorDim;
  switch (mode) {
    case NORMAL:
      color=colorNormal;
      colorDim=colorNormalDim;
      break;
    case GAP:
      color=colorGap;
      colorDim=colorGap;
      break;
    case PRELOOPCROSSING:
      color=colorPreloop;
      colorDim=colorPreloopDim;
      break;
    case LOOPCROSSING:
      color=colorLoop;
      colorDim=colorLoopDim;
      break;
    case AFTERLOOPCROSSING:
      color=colorAfterloop;
      colorDim=colorAfterloopDim;
      break;
    case OBSTACLE:
      color=colorObstacle;
      colorDim=colorObstacleDim;
      break;
    case FLYING:
      color=colorFlying;
      colorDim=colorFlyingDim;
      break;
    case TURN90:
      color=colorTurn90;
      colorDim=colorTurn90Dim;
      break;
    default: // ALLBLACK
      color=colorAllblack;
      colorDim=colorAllblackDim;
  }

  for(i=0; i<9; i++) {
      if (hasLine[i]) {
        signalLights.setPixelColor(i, color);
      }
      else {
        signalLights.setPixelColor(i, colorDim);
      }
    }
    signalLights.show();
}

