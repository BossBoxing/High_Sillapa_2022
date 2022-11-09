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
    move('F',51,700);
    stop(1000);
    move('L',51,700);
    stop(1000);
    move('R',51,700);
    stop(1000);
    move('B',51,700);
    stop(1000);
    // turnLeft(1000);
    // stop(1000);
    // turnRight(1000);
    // stop(1000);
  }
  else if(function == 3){
    oled(0,0,"W: %d ",analog(4));
    delay(100);
    oledClear();
    // readColor();
    // moveEncoder('R',30,30);
    // stop(1000);

  }
  else if(function == 4){
    run('R');
    // readEncoder();
  }
}
