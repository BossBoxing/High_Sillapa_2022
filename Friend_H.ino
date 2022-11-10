#include <ModelPro.h>

int function = 0;

void setup() {
  ok();

}

void loop() {
  if (function == 0){
    readServo();
  }
  else if(function == 1){
    readSensor();
  }
  else if(function == 2){
    run();
  }
  else if(function == 3){
    Check_Front();
  }
  else if(function == 4){
    Check_Right();
  }
}
