/*
Initialize peltier Control library and define pins
Set initial intensity and direction to 0
*/
void initPeltier() {
  PC.begin();
}

/*
Peltier needs to cool or heat
Depending on the water and target temperatur
If not set differently, tempTarget is 24C
*/
void peltierControl() {
  int tempDifference = (inputData.tempWater - inputData.tempTarget) * 10;
    switch(PC.peltierState) {
      case PeltierStopped:
        if(tempDifference <= (-hysteresis - epsilon)) {
          PC.heat(calculatePwm(tempDifference, PC.peltierState));
        } 
        else if (tempDifference >= (hysteresis + epsilon)) {
          PC.cool(calculatePwm(tempDifference, PC.peltierState));
        }
        else {
          PC.stop();
        }    
      break;
      
      case PeltierHeating:
        if ((tempDifference > -hysteresis) && (tempDifference <= 0)) {
          PC.stop();
        }
        else {
          long val = calculatePwm(tempDifference, PC.peltierState);
          if (val != 0) {
            PC.heat(val);
          } 
          else {
            PC.stop();
          }
        }
      break;

      case PeltierCooling:
        if ((tempDifference < hysteresis) && (tempDifference > 0)) {
          PC.stop();
        }
        else {
          long val = calculatePwm(tempDifference, PC.peltierState);
          if (val != 0) {
            PC.cool(val);
          } 
          else {
            PC.stop();
          }
        }
      break;
    }
}

/*
Calculate required PWM value
*/
int calculatePwm(int tempDiff, PeltierState state) {
  int value;
  if (abs(tempDiff) > hysteresis ) {
    value = 255;
  } 
  else {
    value = 0;
  }
  if (value > 255) {
    value = 255;
  }
  if (value < 0) {
    value = 0;
  }
  switch (state) {
    case PeltierStopped:
      peltierPwmValue = 0;
      value = 0;
      break;
      
    case PeltierCooling:
      peltierPwmValue = -value;
      break;
      
    case PeltierHeating:
      peltierPwmValue = value;
      break;
  }
  return value;
}
