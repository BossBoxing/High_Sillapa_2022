#define S_FL analog(0)
#define S_FR analog(1)
#define S_R analog(2)
#define S_G analog(3) 
#define S_B analog(4)
#define S_W analog(5)
#define S_BL analog(6)
#define S_BR analog(7)

int reff_S_FL = 500;
int reff_S_FR = 500;
int reff_S_BL = 500;
int reff_S_BR = 500;

#define Servo_R 1
#define Servo_G 2
#define Servo_B 3
#define Servo_Y 4
#define Servo_Flag 5

int Servo_R_Keep = 120;
int Servo_R_Push = 120;
int Servo_G_Keep = 120;
int Servo_G_Push = 120;
int Servo_B_Keep = 120;
int Servo_B_Push = 120;
int Servo_Y_Keep = 120;
int Servo_Y_Push = 120;
int Servo_Flag_Off = 120;
int Servo_Flag_On = 120;

#define E_FL 1
#define E_FR 2
#define E_BL 18
#define E_BR 19

int pw = 60;
int pwSlow = 30;
int time_default = 100;

// Motor Control
void move(char pos,int pw,int time){
    else if (pos == 'B'){
        motor(1,-pw);
        motor(2,-pw);
        motor(3,-pw);
        motor(4,-pw);
    }
    else if (pos == 'L'){
        motor(1,-pw);
        motor(2,pw);
        motor(3,pw);
        motor(4,-pw);
    }
    else if (pos == 'R'){
        motor(1,pw);
        motor(2,-pw);
        motor(3,-pw);
        motor(4,pw);
    }
    else{
        motor(1,pw);
        motor(2,pw);
        motor(3,pw);
        motor(4,pw);
    }
    delay(time);
}
void turnLeft(int time){
    motor(1,-pw);
    motor(2,pw);
    motor(3,-pw);
    motor(4,pw);
    delay(time);
}
void turnRight(int time){
    motor(1,pw);
    motor(2,-pw);
    motor(3,pw);
    motor(4,-pw);
    delay(time);
}
void stop(int time){
    motor(1,0);
    motor(2,0);
    motor(3,0);
    motor(4,0);
    delay(time);
}

// Servo Control
void onFlag(){
    servo(Servo_Flag,Servo_Flag_On);
    delay(time_default);
}
void offFlag(){
    servo(Servo_Flag,Servo_Flag_Off);
    delay(time_default);
}
void Box_Keep(char color){
    if (color == 'R')
    {
        servo(Servo_R,Servo_R_Keep);
    }
    else if (color == 'G')
    {
        servo(Servo_G,Servo_G_Keep);
    }
    else if (color == 'B')
    {
        servo(Servo_B,Servo_B_Keep);
    }
    else
    {
        servo(Servo_Y,Servo_Y_Keep);
    }
    delay(time_default);
}
void Box_Push(char color){
    if (color == 'R')
    {
        servo(Servo_R,Servo_R_Push);
    }
    else if (color == 'G')
    {
        servo(Servo_G,Servo_G_Push);
    }
    else if (color == 'B')
    {
        servo(Servo_B,Servo_B_Push);
    }
    else
    {
        servo(Servo_Y,Servo_Y_Push);
    }
    delay(time_default);
}

// Functionally for test
void readSensor(){
    oled(0,0 ,"FL:%d ",S_FL);
    oled(0,10,"FR:%d ",S_FR);
    oled(0,20,"BL:%d ",S_BL);
    oled(0,30,"BR:%d ",S_BR);
    oled(50,0 ,"Red:%d ",S_R);
    oled(50,10,"Green:%d ",S_G);
    oled(50,20,"Blue:%d ",S_B);
    oled(50,30,"White:%d ",S_W);
    delay(100);
    oledClear();
}
void readServo(){
    delay(500);
    int p, d;
    while (SW_OK() == 1) {
      p = knob(1, 4);
      oled(1, 4, "Port = %d ", p);
      oledClear();
    }
    delay(500);
    while (SW_OK() == 1) {
      d = knob(1, 180);
      servo(p, d);
      oled(2, 4, "results = %d ", d);
      oledClear();
    }
    oledClear();
}
void readColor(){
    oled(0,0, "R: %d ",map(S_R,0,1023,0,255));
    oled(0,10,"G: %d ",map(S_G,0,1023,0,255));
    oled(0,20,"B: %d ",map(S_B,0,1023,0,255));
    oled(0,30,"W: %d ",map(S_W,0,1023,0,255));
    delay(100);
    oledClear();
}