#include <ModelPro.h>
#include <EEPROM.h>

int function = 0;

// Reference Main Sensor
int reff_FL = 814;
int reff_FR = 777;
int reff_BL = 840;
int reff_BR = 585;

// Reference Color Sensor
int reff_S_R = 178;
int reff_S_G = 185;
int reff_S_B = 165;
int reff_S_G_RY = 170;

int Servo_R_Keep = 13;
int Servo_R_Push = 62;
int Servo_G_Keep = 105;
int Servo_G_Push = 64;
int Servo_B_Keep = 175; // Test
int Servo_B_Push = 127; // Test
int Servo_Y_Keep = 19;
int Servo_Y_Push = 73;
int Servo_Flag_Off = 5;
int Servo_Flag_On = 175;

int pw = 35;
int pwSlow = 25;
int pwTurn= 35;
int pwSlowCaribate = 20;
int time_default = 100;

int encoder_turn_L = 72;
int encoder_turn_R = 73;
int encoder_turn_U = 148;

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
    moveEncoderPure('F' , pw , 30);
    while(1)
    {
      run();
    }
  }
  else if(function == 3){
    Check_Front();
  }
  else if(function == 4){
    Check_Right();
  }
}
