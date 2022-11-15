#include <ModelPro.h>
#include <EEPROM.h>

int function = 0;

/////////////////////////////////
////// Setting - START //////////
/////////////////////////////////

// Initial Value of All Servo
int Servo_R_Keep = 13; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีแดง
int Servo_R_Push = 62; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีแดง
int Servo_G_Keep = 105; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีเขียว
int Servo_G_Push = 64; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีเขียว
int Servo_B_Keep = 175; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีน้ำเงิน
int Servo_B_Push = 127; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีน้ำเงิน
int Servo_Y_Keep = 19; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีเหลือง
int Servo_Y_Push = 73; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีเหลือง
int Servo_Flag_Off = 5; // ค่าเซอร์โวในการเก็บธง
int Servo_Flag_On = 175; // ค่าเซอร์โวในการยกธง

// motor control
int pw = 55; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ
int pwSlow = 45; // กำลังมอเตอร์ ในการวิ่ง แบบชะลอ
int pwTurn= 55; // กำลังมอเตอร์ ในการเลี้ยว
int pwSlowCaribate = 45; // กำลังมอเตอร์ ในการวิ่ง เช็คเส้น
int pwWave = 60; // กำลังมอเตอร์ ในการวิ่ง ข้ามลูกระนาด

int time_default = 100; // เวลาในการหยุด (ms.) หน่วยเป็น มิลลิวินาที

int encoder_turn_L = 260; // จำนวนรอบในการเลี้ยวซ้าย
int encoder_turn_R = 260; // จำนวนรอบในการเลี้ยวขวา
int encoder_turn_U = 510;  // จำนวนรอบในการเลี้ยวขวา กลับหลังหัน

// value of check
int check_blackline = 13; // ค่า ระยะทาง (cm.) เดินสไลด์ซ้าย/ขวา ออกไปเพื่อเช็คเส้นดำ
int check_frontblackline = 28; // ค่า ระยะทาง (cm.) เดินตรงขึ้นไปเช็ตเส้นดำด้านหน้า
int return_from_caribate = 5; // ค่า ระยะทาง (cm.) กลับมาจุดตรงกลางหลังจากสไลด์ออกไปเช็คด้านข้าง
int go_from_colors = 20; // ค่า ระยะทาง (cm.) หลังจากวางลูกบาศก์เรียบร้อย 
                        // กลับหลังหันและต้องการเดินตรงขึ้นมาอยู่ตรงกลางของบล็อคต่อไป

// value of sapan
int go_up_sapan = 35; // ค่า ระยะทาง (cm.) ในการขึ้นสะพานไปอยู่แผ่นข้างบน
int go_down_sapan = 55; // ค่า ระยะทาง (cm.) ในการเดินจากบนสะพาน ลงมาแผ่นด้านล่าง

// value of wave (ranard)
int go_wave = 50; // ค่า ระยะทาง (cm.) ในการเดินตรงไปจากแผ่นลูกระนาด

///////////////////////////////
////// Setting - END //////////
///////////////////////////////

void setup() {
  ok();

}

void loop() {
  if (function == 0){

    moveEncoderPure('F' , pw , check_frontblackline);
    while(1)
    {
      run();
    }

  }
  else if(function == 1){
    moveEncoderPure('F' , pw , check_frontblackline);
    while(1)
    {
      run();
    }
    

  }
  else if(function == 2){
    moveEncoderPure('F' , pw , check_frontblackline);
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
    test();
    // encoder_reset(2);
    // while(1)
    // {
    //   oled(0,0,"%d ",encoder(2));
    //   delay(100);
    //   oledClear();
    // }
    // turnLeftEncoder(encoder_turn_L);
    // Wait();
    // turnRightEncoder(encoder_turn_R);
    // Wait();
  }
}
