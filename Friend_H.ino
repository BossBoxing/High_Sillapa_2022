#include <ModelPro.h>
#include <EEPROM.h>

int function = 0;

// Reference Main Sensor
#define startAddressMainSensor 40
int reff_FL = EEPROM.read(startAddressMainSensor + 1) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 1);
int reff_FR = EEPROM.read(startAddressMainSensor + 2) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 2);
int reff_BL = EEPROM.read(startAddressMainSensor + 3) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 3);
int reff_BR = EEPROM.read(startAddressMainSensor + 4) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 4);

// Reference Color Sensor
#define startAddressColorSensor 20
int reff_S_R = EEPROM.read(startAddressColorSensor + 1) == 255 ? 178 : EEPROM.read(startAddressColorSensor + 1);
int reff_S_G = EEPROM.read(startAddressColorSensor + 2) == 255 ? 185 : EEPROM.read(startAddressColorSensor + 2);
int reff_S_B = EEPROM.read(startAddressColorSensor + 3) == 255 ? 165 : EEPROM.read(startAddressColorSensor + 3);
int reff_S_G_RY = EEPROM.read(startAddressColorSensor + 4) == 255 ? 170 : EEPROM.read(startAddressColorSensor + 4);

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
int pwSlow = 35;
int pwTurn= 35;
int pwSlowCaribate = 25;
int time_default = 100;

int encoder_turn_L = 72;
int encoder_turn_R = 75;
int encoder_turn_U = 153;

// value of check
int check_blackline = 13; // 15 // 12
int check_frontblackline = 27;
int return_from_caribate = 5;

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
    readServo();
  }
  else if(function == 2){
    readSensor();
  }
  else if(function == 3){
    setColorSensorReff();
  }
  else if(function == 4){
    setMainSensorReff();
  }
}
