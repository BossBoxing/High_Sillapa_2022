#include <ModelPro.h>
#include <EEPROM.h>
#include "MPU6050.h"

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
int pw = 50; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ
int pwSlow = 40; // กำลังมอเตอร์ ในการวิ่ง แบบชะลอ
int pwTurn= 50; // กำลังมอเตอร์ ในการเลี้ยว
int pwSlowCaribate = 35; // กำลังมอเตอร์ ในการวิ่ง เช็คเส้น
int pwWave = 40; // กำลังมอเตอร์ ในการวิ่ง ข้ามลูกระนาด

int pwL = 53; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ
int pwR = 55; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ

int time_default = 200; // เวลาในการหยุด (ms.) หน่วยเป็น มิลลิวินาที

int encoder_turn_L = 1050; // จำนวนรอบในการเลี้ยวซ้าย
int encoder_turn_R = 1050; // จำนวนรอบในการเลี้ยวขวา
int encoder_turn_U = 2000;  // จำนวนรอบในการเลี้ยวขวา กลับหลังหัน

// value of check
int check_blackline = 600; // ค่า ระยะทาง (cm.) เดินสไลด์ซ้าย/ขวา ออกไปเพื่อเช็คเส้นดำ
int check_frontblackline = 1250; // ค่า ระยะทาง (cm.) เดินตรงขึ้นไปเช็ตเส้นดำด้านหน้า
int return_from_caribate = 500; // ค่า ระยะทาง (cm.) กลับมาจุดตรงกลางหลังจากสไลด์ออกไปเช็คด้านข้าง
int go_from_colors = 700; // ค่า ระยะทาง (cm.) หลังจากวางลูกบาศก์เรียบร้อย 
                        // กลับหลังหันและต้องการเดินตรงขึ้นมาอยู่ตรงกลางของบล็อคต่อไป
int in_color = 300;

// value of sapan
int go_up_sapan = 1500; // ค่า ระยะทาง (cm.) ในการขึ้นสะพานไปอยู่แผ่นข้างบน
int go_down_sapan = 2500; // ค่า ระยะทาง (cm.) ในการเดินจากบนสะพาน ลงมาแผ่นด้านล่าง

// value of wave (ranard)
int go_wave = 50; // ค่า ระยะทาง (cm.) ในการเดินตรงไปจากแผ่นลูกระนาด

// sapan
int reff_sapan = 102; // ค่ากึ่งกลาง ระหว่าง พื้นปกติกับสะพาน

///////////////////////////////
////// Setting - END //////////
///////////////////////////////
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int valx , valy , valz;
void setup() {
  ok();
  mpu.initialize();
}

void loop() {
  if (function == 0){

    // moveEncoderPure('F' , pw , check_frontblackline);
    while(1)
    {
      run();
    }

  }
  else if(function == 1){
    // moveEncoderPure('F' , pw , check_frontblackline);
    while(1)
    {
      run();
    }
    

  }
  else if(function == 2){
    // moveEncoderPure('F' , pw , check_frontblackline);
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
    // test();
    // Wait();
    // test();
    // encoder_reset(2);
    // while(1)
    // {
    //   oled(0,0,"%d ",encoder(2));
    //   delay(100);
    //   oledClear();
    // }
    // moveEncoder('F', pw, 30);
    // move('F', pw, 2000);

    // Wait();
    setTextSize(2);
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  valx = map(ax, -17000, 17000, 0, 179);
  valy = map(ay, -17000, 17000, 0, 179);
  valz = map(az, -17000, 17000, 0, 179);
  oled(0,0,"x : %d ", ax);
  oled(0,20,"y : %d ", ay);
  oled(0,40,"z : %d ", az);
  delay(100);
  oledClear();
  }
}
