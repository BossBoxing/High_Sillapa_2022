#include <ModelPro.h>
#include <EEPROM.h>

int function = 0;

/////////////////////////////////
////// Setting - START //////////
/////////////////////////////////

// Initial Value of All Servo
int Servo_R_Keep = 13;
int Servo_R_Push = 62;
int Servo_G_Keep = 105;
int Servo_G_Push = 64;
int Servo_B_Keep = 175;
int Servo_B_Push = 127;
int Servo_Y_Keep = 19;
int Servo_Y_Push = 73;
int Servo_Flag_Off = 5;
int Servo_Flag_On = 175;

// motor control
int pw = 35; // normal power
int pwSlow = 35; // slow power
int pwTurn= 35; // turn left/right power
int pwSlowCaribate = 25; // caribate power
int pwWave = 55; // go wave power

int time_default = 100; // time stop

int encoder_turn_L = 72; // n of encoder for turn left
int encoder_turn_R = 70; // n of encoder for turn right
int encoder_turn_U = 152; // n od encoder for uturn / return the robot

// value of check
int check_blackline = 13; // left&right go check blackline
int check_frontblackline = 28; // go straight for check blackline
int return_from_caribate = 5; // return to center block map from black line

// value of sapan
int go_up_sapan = 35;
int go_down_sapan = 55;

// value of wave (ranard)
int go_wave = 40;

///////////////////////////////
////// Setting - END //////////
///////////////////////////////

void setup() {
  ok();

}

void loop() {
  if (function == 0){

    moveEncoderPure('F' , pw , 30);
    while(1)
    {
      run();
    }

  }
  else if(function == 1){
    moveEncoderPure('F' , pw , 30);
    while(1)
    {
      run();
    }
    

  }
  else if(function == 2){
    moveEncoderPure('F' , pw , 30);
    while(1)
    {
      run();
    }
    

  }
  else if(function == 3){
    readServo();

    // setColorSensorReff();

  }
  else if(function == 4){
    readSensor();
  }
  else if (function == 5)
  {
    setColorSensorReff();
  }
  else if (function == 6)
  {
    setMainSensorReff();
  }
  else if (function == 7)
  {
    while (1)
    {
      readReff();
      // oled(0, 0, "48: %d", in(48));
      // oled(0, 10, "49: %d", in(49));
      // oled(0, 20, "50: %d", in(50));
      // oled(0, 30, "A12: %d", analog(12));
      // delay(100);
      // oledClear();
    }
  }
}
