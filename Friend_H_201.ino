#include <ModelPro.h>
#include <EEPROM.h>
#include <MPU6050.h>

int function = 0;

/////////////////////////////////
////// Setting - START //////////
/////////////////////////////////

// Initial Value of All Servo
int Servo_R_Keep = 30; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีแดง
int Servo_R_Push = 101; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีแดง
int Servo_G_Keep = 119; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีเขียว
int Servo_G_Push = 53; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีเขียว
int Servo_B_Keep = 115; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีน้ำเงิน
int Servo_B_Push = 55; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีน้ำเงิน
int Servo_Y_Keep = 21; // ค่าเซอร์โวในการเก็บลูกบาศก์ในกลไก สีเหลือง
int Servo_Y_Push = 69; // ค่าเซอร์โวในการเตะลูกบาศก์ออกจากหุ่น สีเหลือง
int Servo_Flag_Off = 1; // ค่าเซอร์โวในการเก็บธง
int Servo_Flag_On = 171; // ค่าเซอร์โวในการยกธง

int encoder_turn_L = 1046; // จำนวนรอบในการเลี้ยวซ้าย
int encoder_turn_R = 1029; // จำนวนรอบในการเลี้ยวขวา
int encoder_turn_U = 2060;  // จำนวนรอบในการเลี้ยวขวา กลับหลังหัน

// value of checks
int check_blackline = 520; // ค่า ระยะทาง (cm.) เดินสไลด์ซ้าย/ขวา ออกไปเพื่อเช็คเส้นดำ
int check_frontblackline = 1325; // ค่า ระยะทาง (cm.) เดินตรงขึ้นไปเช็ตเส้นดำด้านหน้า
int return_from_caribate = 450; // ค่า ระยะทาง (cm.) กลับมาจุดตรงกลางหลังจากสไลด์ออกไปเช็คด้านข้าง
int go_from_colors = 950; // ค่า ระยะทาง (cm.) หลังจากวางลูกบาศก์เรียบร้อย 
                        // กลับหลังหันและต้องการเดินตรงขึ้นมาอยู่ตรงกลางของบล็อคต่อไป
int in_color = 250; // เดินขึ้นไป เพื่อวางสี **กรณีหุ่นยนต์เดินหน้าเข้าไปปล่อยลูกบาศก์น้อย ให้เพิ่มค่านี้

// blackhole / หลุมดำ
int bk_blackhole = 500; // ค่าถอยหลัง หลังจากเจอหลุมดำ

// value of sapan
int go_up_sapan = 1700; // ค่า ระยะทาง (cm.) ในการขึ้นสะพานไปอยู่แผ่นข้างบน
int go_down_sapan = 2650; // ค่า ระยะทาง (cm.) ในการเดินจากบนสะพาน ลงมาแผ่นด้านล่าง

// value of wave (ranard)
int go_wave = 1350; // ค่า ระยะทาง (cm.) ในการเดินตรงไปจากแผ่นลูกระนาด

// sapan
int reff_sapan = 95; // ค่ากึ่งกลาง ระหว่าง พื้นปกติกับสะพาน
int begin_obstacle = 900; // ค่าวิ่งหลังจากชนสวิตซ์ เพื่อเข้าไปเช็คว่าเป็นสะพาน หรือลูกระนาด
int stop_for_check = 1000; // หยุดก่อนเช็คไจโร หรือความเอียงของหุ่นยนต์

// motor control
int pw = 50; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ
int pwSlow = 40; // กำลังมอเตอร์ ในการวิ่ง แบบชะลอ
int pwTurn= 50; // กำลังมอเตอร์ ในการเลี้ยว
int pwSlowCaribate = 35; // กำลังมอเตอร์ ในการวิ่ง เช็คเส้น
int pwWave = 40; // กำลังมอเตอร์ ในการวิ่ง ข้ามลูกระนาด

int pwL = 55; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ ล้อฝั่งซ้าย
int pwR = 55; // กำลังมอเตอร์ ในการวิ่ง แบบปกติ ล้อฝั่งขวา

int time_default = 200; // เวลาในการหยุด (ms.) หน่วยเป็น มิลลิวินาที
int time_check_color = 200; // เวลาในการหยุด (ms.) ก่อนเช็คสีพื้น

///////////////////////////////
////// Setting - END //////////
///////////////////////////////

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int valx , valy , valz;
void setup() {
  //mpu.initialize();
  ok();
  mpu.initialize();
}

void loop() {
  if (function == 0){

    move('F' , pw , check_frontblackline);
    stop(time_default);
    while(1)
    {
      run_L();
    }

  }
  else if(function == 1){
    move('F' , pw , check_frontblackline);
    stop(time_default);
    while(1)
    {
      run_L();
    }
    

  }
  else if(function == 2){
    move('F' , pw , check_frontblackline);
    stop(time_default);
    while(1)
    {
      run_L();
    }
    

  }
  else if(function == 3){
    move('F' , pw , check_frontblackline);
    stop(time_default);
    while(1)
    {
      run_R();
    }
    

  }
  else if(function == 4){
    move('F' , pw , check_frontblackline);
    stop(time_default);
    while(1)
    {
      run_R();
    }
    

  }
  else if(function == 5){
    move('F' , pw , check_frontblackline);
    stop(time_default);
    while(1)
    {
      run_R();
    }
    

  }
  else if(function == 6){
    readServo();

    // setColorSensorReff();

  }
  else if(function == 7){
    readSensor();
  }
  else if (function == 8)
  {
    setColorSensorReff();
  }
  else if (function == 9)
  {
    setMainSensorReff();
  }
  else if (function == 10)
  {
    readFloorColor();
  }
  else if (function == 11)
  {
    oled(0, 0, "Angle : %d ", getAngleOfRobot());
    delay(100);
    oledClear();
    // Debug Function for Test
    // test();
  }
}
