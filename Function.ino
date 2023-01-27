// Initial Variables Port
#define S_FL map(analog(0), 0, 1023, 0, 100)
#define S_R map(analog(1), 0, 1023, 0, 255)
#define S_G map(analog(2), 0, 1023, 0, 255)
#define S_B map(analog(3), 0, 1023, 0, 255)
#define S_FR map(analog(4), 0, 1023, 0, 100)
#define S_BL map(analog(5), 0, 1023, 0, 100)
#define S_BR map(analog(6), 0, 1023, 0, 100)

#define S_SW in(49)

#define Servo_R 1
#define Servo_G 2
#define Servo_B 3
#define Servo_Y 4
#define Servo_Flag 5

// Reference Main Sensor
#define startAddressMainSensor 80
int reff_FL = EEPROM.read(startAddressMainSensor + 1) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 1);
int reff_FR = EEPROM.read(startAddressMainSensor + 2) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 2);
int reff_BL = EEPROM.read(startAddressMainSensor + 3) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 3);
int reff_BR = EEPROM.read(startAddressMainSensor + 4) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 4);
int reff_FL_BB = EEPROM.read(startAddressMainSensor + 5) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 5);
int reff_FR_BB = EEPROM.read(startAddressMainSensor + 6) == 255 ? 50 : EEPROM.read(startAddressMainSensor + 6);

// Reference Color Sensor
#define startAddressColorSensor 20
int reff_S_R = EEPROM.read(startAddressColorSensor + 1) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 1);
int reff_S_G = EEPROM.read(startAddressColorSensor + 2) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 2);
int reff_S_B = EEPROM.read(startAddressColorSensor + 3) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 3);
int reff_R_Black = EEPROM.read(startAddressColorSensor + 1) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 1);
int reff_G_Black = EEPROM.read(startAddressColorSensor + 2) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 2);
int reff_B_Black = EEPROM.read(startAddressColorSensor + 3) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 3);
int reff_R_Red = EEPROM.read(startAddressColorSensor + 4) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 4);
int reff_G_Red = EEPROM.read(startAddressColorSensor + 5) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 5);
int reff_B_Red = EEPROM.read(startAddressColorSensor + 6) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 6);
int reff_R_Green = EEPROM.read(startAddressColorSensor + 7) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 7);
int reff_G_Green = EEPROM.read(startAddressColorSensor + 8) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 8);
int reff_B_Green = EEPROM.read(startAddressColorSensor + 9) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 9);
int reff_R_Blue = EEPROM.read(startAddressColorSensor + 10) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 10);
int reff_G_Blue = EEPROM.read(startAddressColorSensor + 11) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 11);
int reff_B_Blue = EEPROM.read(startAddressColorSensor + 12) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 12);
int reff_R_Yellow = EEPROM.read(startAddressColorSensor + 13) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 13);
int reff_G_Yellow = EEPROM.read(startAddressColorSensor + 14) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 14);
int reff_B_Yellow = EEPROM.read(startAddressColorSensor + 15) == 255 ? 50 : EEPROM.read(startAddressColorSensor + 15);

int diff_for_color = 29; // ค่าความต่าง ของแต่ละค่าแสง
int reff_blackhole = 1300;
// Flag
int flagState = 0;
int Pos_Robot = 0; // L = 0;, R = 1;

unsigned long looptime = 0;

// Motor Control
void move(char pos, int pw, int time)
{
    if (pos == 'B')
    {
        Motor(1, -pw);
        Motor(2, -pw);
        Motor(3, -pw);
        Motor(4, -pw);
    }
    else if (pos == 'L')
    {
        Motor(1, -pw);
        Motor(2, pw);
        Motor(3, pw);
        Motor(4, -pw);
    }
    else if (pos == 'R')
    {
        Motor(1, pw);
        Motor(2, -pw);
        Motor(3, -pw);
        Motor(4, pw);
    }
    else
    {
        Motor(1, pwL);
        Motor(2, pwR);
        Motor(3, pwL);
        Motor(4, pwR);
    }
    delay(time);
}
void turnLeft(int pw, int time)
{
    Motor(1, -pw);
    Motor(2, pw);
    Motor(3, -pw);
    Motor(4, pw);
    delay(time);
}
void turnRight(int pw, int time)
{
    Motor(1, pw);
    Motor(2, -pw);
    Motor(3, pw);
    Motor(4, -pw);
    delay(time);
}
void stop(int time)
{
    Motor(1, 0);
    Motor(2, 0);
    Motor(3, 0);
    Motor(4, 0);
    delay(time);
}

// Servo Control
void onFlag()
{
    servo(Servo_Flag, Servo_Flag_On);
    delay(time_default);
}
void offFlag()
{
    servo(Servo_Flag, Servo_Flag_Off);
    delay(time_default);
}

// Box
int box_count = 0;
void Box_Keep(char color)
{
    if (color == 'R')
    {
        servo(Servo_R, Servo_R_Keep);
    }
    else if (color == 'G')
    {
        servo(Servo_G, Servo_G_Keep);
    }
    else if (color == 'B')
    {
        servo(Servo_B, Servo_B_Keep);
    }
    else
    {
        servo(Servo_Y, Servo_Y_Keep);
    }
    delay(time_default);
}
void Box_Push(char color)
{
    stop(time_default);
    if (color == 'R')
    {
        for (int i = Servo_R_Keep; i < Servo_R_Push; i++)
        {
            /* code */
            servo(Servo_R, i);
            delay(10);
        }
    }
    else if (color == 'G')
    {
        // servo(Servo_G, Servo_G_Push);
        for (int i = Servo_G_Keep; i > Servo_G_Push; i -= 1)
        {
            /* code */
            servo(Servo_G, i);
            delay(10);
        }
    }
    else if (color == 'B')
    {
        // servo(Servo_B, Servo_B_Push);
        for (int i = Servo_B_Keep; i > Servo_B_Push; i -= 1)
        {
            /* code */
            servo(Servo_B, i);
            delay(10);
        }
    }
    else
    {
        // servo(Servo_Y, Servo_Y_Push);
        for (int i = Servo_Y_Keep; i < Servo_Y_Push; i++)
        {
            /* code */
            servo(Servo_Y, i);
            delay(10);
        }
    }
    delay(400);

    // check box
    box_count++;
    if (box_count >= 4)
    {
        Finish();
    }
}

// Encoder Motor Control
void moveEncoderPure(char pos, int pw, int cm)
{
    stop(time_default);
    if (pos == 'B')
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            move('B', pw, 1);
        }
    }
    else if (pos == 'L')
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            move('L', pw, 1);
        }
    }
    else if (pos == 'R')
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            move('R', pw, 1);
        }
    }
    else
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            // trackLine();
            move('F', pw, 1);
        }
    }
    stop(time_default);
}
void moveEncoder(char pos, int pw, int cm)
{
    stop(time_default);
    if (pos == 'B')
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            move('B', pw, 1);
        }
    }
    else if (pos == 'L')
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            move('L', pw, 1);
        }
    }
    else if (pos == 'R')
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            move('R', pw, 1);
        }
    }
    else
    {
        encoder_reset(2);
        int Cm = (cm / 0.029);
        while (encoder(2) < Cm)
        {
            trackLine();
            // move('F', pw, 1);
        }
    }
    stop(time_default);
}
void turnLeftEncoder(int bit)
{
    stop(time_default);
    encoder_reset(2);
    while (encoder(2) < bit)
    {
        turnLeft(pwTurn, 1);
    }
    stop(time_default);
}
void turnRightEncoder(int bit)
{
    stop(time_default);
    encoder_reset(2);
    while (encoder(2) < bit)
    {
        turnRight(pwTurn, 1);
    }
    stop(time_default);
}
void uTurn()
{
    turnRight(pwTurn, encoder_turn_U);
}

// TrackLine
void turnLeftTrack()
{
    Motor(1, 5);
    Motor(2, pw);
    Motor(3, 5);
    Motor(4, pw);
    delay(10);
}
void turnRightTrack()
{
    Motor(1, pw);
    Motor(2, 5);
    Motor(3, pw);
    Motor(4, 5);
    delay(10);
}
void trackLine() // Used on moveEncoder('F')
{
    if (S_FR < reff_FR && S_R > reff_S_R && S_B > reff_S_B && S_FL > reff_FL)
    {
        // Normal Track
        // TL
        turnLeftTrack();
    }
    else if (S_FL < reff_FL && S_R > reff_S_R && S_B > reff_S_B && S_FR > reff_FR)
    {
        // Normal Track
        // TR
        turnRightTrack();
    }
    else if (S_FR < reff_FR)
    {
        // Found Black Track
        // TR
        turnRight(pwSlowCaribate, 1);
        // turnRightTrack();
    }
    else if (S_FL < reff_FL)
    {
        // Found Black Track
        // TL
        turnLeft(pwSlowCaribate, 1);
        // turnLeftTrack();
    }
    else
    {
        move('F', pw, 10);
    }
}
void turnLeftTrack_Stop()
{
    turnLeftTrack();
    // Motor(1, 5);  Motor(2, pw);
    // Motor(3, 5);  Motor(4, pw);
    // delay(10);
}
void turnRightTrack_Stop()
{
    turnRightTrack();
    // Motor(1, pw);   Motor(2, 5);
    // Motor(3, pw);   Motor(4, 5);
    // delay(10);
}
void trackLine_R() // Used on Check_Right()
{
    if (S_FR < reff_FR && S_BR > reff_BR)
    {
        // TL
        turnLeftTrack_Stop();
    }
    else if (S_FR > reff_FR && S_BR < reff_BR)
    {
        // TR
        turnRightTrack_Stop();
    }
    else
    {
        move('R', pw, 10);
    }
}
void trackLine_L() // Used on Check_Left()
{
    if (S_BL < reff_BL && S_FL > reff_FL)
    {
        // TL
        turnLeftTrack_Stop();
    }
    else if (S_BL > reff_BL && S_FL < reff_FL)
    {
        // TR
        turnRightTrack_Stop();
    }
    else
    {
        move('L', pw, 10);
    }
}
void trackLine_R(int time) // Used on Check_Right()
{
    unsigned long LoopTime=millis();
    while(millis()-LoopTime < time){
        trackLine_R();
    }
}
void trackLine_L(int time) // Used on Check_Left()
{
    unsigned long LoopTime=millis();
    while(millis()-LoopTime < time){
        trackLine_L();
    }
}

// Functionally for test
void readSensor()
{
    oled(0, 0, "FL:%d ", S_FL);
    oled(0, 10, "FR:%d ", S_FR);
    oled(0, 20, "BL:%d ", S_BL);
    oled(0, 30, "BR:%d ", S_BR);
    oled(50, 0, "Red:%d ", S_R);
    oled(50, 10, "Green:%d ", S_G);
    oled(50, 20, "Blue:%d ", S_B);
    // oled(50, 30, "White:%d ", S_W);
    delay(100);
    oledClear();
}
void readServo()
{
    delay(500);
    int p, d;
    while (SW_OK() == 1)
    {
        p = knob(1, 6);
        oled(1, 4, "Port = %d ", p);
        oledClear();
    }
    delay(500);
    while (SW_OK() == 1)
    {
        d = knob(1, 180);
        servo(p, d);
        oled(2, 4, "results = %d ", d);
        oledClear();
    }
    oledClear();
}
void readColor()
{
    oled(0, 0, "R: %d ", S_R);
    oled(0, 10, "G: %d ", S_G);
    oled(0, 20, "B: %d ", S_B);
    // oled(0, 30, "W: %d ", S_W);
    delay(100);
    oledClear();
}
void readEncoder()
{

    encoder_reset(2);
    encoder_reset(2);

    while (1)
    {
        oled(0, 0, "en(2) : %d  ", encoder(2));
        oled(0, 10, "en(3) : %d  ", encoder(2));
        delay(100);
        oledClear();
    }
}
void readReff()
{
    oled(0, 0, "%d ", reff_S_R);
    oled(0, 10, "%d ", reff_S_G);
    oled(0, 20, "%d ", reff_S_B);
    // oled(0, 30, "%d ", reff_S_G_RY);
    delay(100);
    oledClear();
}
void readFloorColor() {
  if (getColorByRGB() == 1) {
    oledClear();
    setTextSize(2);
    oled(0, 0, "Red       ");
  }
  else if (getColorByRGB() == 2) {
    oledClear();
    setTextSize(2);
    oled(0, 0, "Green       ");
  }
  else if (getColorByRGB() == 3) {
    oledClear();
    setTextSize(2);
    oled(0, 0, "Blue       ");
  }
  else if (getColorByRGB() == 4) {
    oledClear();
    setTextSize(2);
    oled(0, 0, "Yellow       ");
  }
  else {
    oledClear();
    setTextSize(2);
    oled(0, 0, "Black/etc.     ");
  }
}
void Wait()
{
    stop(time_default);
    beep();
    while (SW_OK() == 1)
    {
    }
    while (SW_OK() == 0)
    {
    }
    beep();
}

// Caribate for Straight
void Caribate(char pos)
{
    if (pos == 'L')
    {
        // move('R', pwSlowCaribate, 500);
        stop(time_default);
        while (S_FL > reff_FL || S_BL > reff_BL)
        {
            if (S_G < reff_S_G)
            {
                move('B', pwSlowCaribate, 50);
            }
            else if (S_FL < reff_FL)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else if (S_BL < reff_BL)
            {
                turnLeft(pwSlowCaribate, 10);
            }
            else
            {
                move('L', pwSlowCaribate, 10);
            }
        }
    }
    else if (pos == 'R')
    {
        // move('L', pwSlowCaribate, 500);
        stop(time_default);
        while (S_FR > reff_FR || S_BR > reff_BR)
        {
            if (S_B < reff_S_B)
            {
                move('B', pwSlowCaribate, 50);
            }
            else if (S_FR < reff_FR)
            {
                turnLeft(pwSlowCaribate, 10);
            }
            else if (S_BR < reff_BR)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else
            {
                move('R', pwSlowCaribate, 10);
            }
        }
        stop(30);
        while (S_FR > reff_FR || S_BR > reff_BR)
        {
            move('R', pwSlowCaribate, 10);
        }
        // move('R',pwSlowCaribate,50);
    }
    else if (pos == 'B')
    {
        move('F', pwSlowCaribate, 300);
        stop(time_default);
        while (S_BL > reff_BL || S_BR > reff_BR)
        {
            if (S_BL < reff_BL)
            {
                turnRight(pwSlowCaribate, 1);
            }
            else if (S_BR < reff_BR)
            {
                turnLeft(pwSlowCaribate, 1);
            }
            else
            {
                move('B', pwSlowCaribate, 1);
            }
        }
    }
    else // F
    {
        move('B', pwSlowCaribate, 300);
        stop(time_default);
        while (S_FL > reff_FL || S_FR > reff_FR)
        {
            if (S_FL < reff_FL)
            {
                turnLeft(pwSlowCaribate, 10);
            }
            else if (S_FR < reff_FR)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else
            {
                move('F', pwSlowCaribate, 10);
            }
        }
        stop(time_default);

        // 2
        move('B', pwSlowCaribate, 300);
        stop(time_default);
        while (S_FL > reff_FL || S_FR > reff_FR)
        {
            if (S_FL < reff_FL)
            {
                turnLeft(pwSlowCaribate, 10);
            }
            else if (S_FR < reff_FR)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else
            {
                move('F', pwSlowCaribate, 10);
            }
        }
        stop(time_default);
        // stop(time_default);
        // move('F', pwSlowCaribate, 70);
        // stop(30);
    }
    stop(time_default);
}
void Caribate_Color()
{
    // moveEncoder('R',pwSlowCaribate,4);
    while (S_FL < reff_FL || S_FR < reff_FR)
    {
        if (S_FL > reff_FL)
        {
            turnRight(pwSlowCaribate, 10);
        }
        else if (S_FR > reff_FR)
        {
            turnLeft(pwSlowCaribate, 10);
        }
        else
        {
            move('B', pwSlowCaribate, 10);
        }
    }
    stop(time_default);
}
// function for usefully
int getEncoderCentimater(int cm)
{
    return (cm / 0.029);
}
int getColorByRGB()
{
    // if (S_R < reff_R_Black && S_G < reff_G_Black && S_B < reff_B_Black)
    // {
    //     return 0; // Black
    // }
    if ( ( S_R > (reff_R_Red - diff_for_color) && S_R < (reff_R_Red + diff_for_color) ) &&
    ( S_G > (reff_G_Red - diff_for_color) && S_G < (reff_G_Red + diff_for_color) ) &&
    ( S_B > (reff_B_Red - diff_for_color) && S_B < (reff_B_Red + diff_for_color) )
    )
    {
        return 1; // Red
    }
    else if ( ( S_R > (reff_R_Green - diff_for_color) && S_R < (reff_R_Green + diff_for_color) ) &&
    ( S_G > (reff_G_Green - diff_for_color) && S_G < (reff_G_Green + diff_for_color) ) &&
    ( S_B > (reff_B_Green - diff_for_color) && S_B < (reff_B_Green + diff_for_color) )
    )
    {
        return 2; // Green
    }
    else if ( ( S_R > (reff_R_Blue - diff_for_color) && S_R < (reff_R_Blue + diff_for_color) ) &&
    ( S_G > (reff_G_Blue - diff_for_color) && S_G < (reff_G_Blue + diff_for_color) ) &&
    ( S_B > (reff_B_Blue - diff_for_color) && S_B < (reff_B_Blue + diff_for_color) )
    )
    {
        return 3; // Blue
    }
    else if ( ( S_R > (reff_R_Yellow - diff_for_color) && S_R < (reff_R_Yellow + diff_for_color) ) &&
    ( S_G > (reff_G_Yellow - diff_for_color) && S_G < (reff_G_Yellow + diff_for_color) ) &&
    ( S_B > (reff_B_Yellow - diff_for_color) && S_B < (reff_B_Yellow + diff_for_color) )
    )
    {
        return 4; // Yellow
    }
    else
    {
       return 0; // Black or Error
    }
}
int getAngleOfRobot(){
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    valy = map(ay, -17000, 17000, 0, 179);
    return valy;
}
// Pattern
void run_R()
{
  Pos_Robot = 1;
  if (flagState == 0)
  {
    Check_Right();
  }
  else if (flagState == 1)
  {
    Check_Front();
  }
  else if (flagState == 2)
  {
    Check_Left();
  }
}
void run_L()
{
  Pos_Robot = 0;
  if (flagState == 0)
  {
    Check_Left();
  }
  else if (flagState == 1)
  {
    Check_Front();
  }
  else if (flagState == 2)
  {
    Check_Right();
  }
}
void movePass(int pw, int time, int black_cm)
{
  unsigned long TimeBlack = millis();
  stop(time_default);

  // encoder_reset(2);
  // int Cm = (cm / 0.029);
  flagState = 1;
  looptime = millis();
  while (1)
  {
    if (S_FL < reff_FL && S_FR < reff_FR)
    {
      if (millis() - TimeBlack <= reff_blackhole) {
        stop(time_default);
        Caribate('F');
        Check_Color_F();
        if (flagState != 0)
        {
          move('B', pw, bk_blackhole);
          stop(time_default);
          if (Pos_Robot == 1) {
            turnLeft(pwTurn, encoder_turn_L);
          }
          else {
            turnRight(pwTurn, encoder_turn_R);
          }
          stop(time_default);
          // flagState=0;
          flagState = 1;
        }
        break;
      }
      else
      {
        stop(time_default);
        Caribate('F');
        Check_Color_F();
        if (flagState != 0)
        {
          move('B', pw, black_cm);
          stop(time_default);
        }
        flagState = 0;
      }
      break;
    }
    if ((millis() - looptime) > time)
    {
      stop(time_default);
      if (S_FL < reff_FL || S_FR < reff_FR) {
        Caribate('F');
        Check_Color_F();
        if (flagState != 0)
        {
          move('B', pw, black_cm);
          stop(time_default);
        }
        flagState = 0;
      }
      // Wait();
      flagState = 0;
      break;
    }
    Check_Obstacle();

    // Running..
    trackLine();
  }
  stop(time_default);
}
void Check_Right()
{
  // Setting
  // encoder_reset(2);
  int check_cm = check_blackline;
  int check_diff_cm = 0;
  int black_cm = return_from_caribate;
  int pass_cm = check_frontblackline;

  looptime = millis();
  // Do
  while (1)
  {
    // Condition
    if (S_FR < reff_FR && S_BR < reff_BR) // Found Black
    {
      if (Pos_Robot == 0) {
        stop(time_default);
        Caribate('R');
        stop(time_default);
        move('L', pw, black_cm); // Comeback to pos
        stop(time_default);
        uTurn();
        stop(time_default);
        Caribate('L');
        stop(time_default);
        move('R', pwSlowCaribate, black_cm); // Comeback to pos
        stop(time_default);
        move('F', pw, pass_cm); // Comeback to pos
        stop(time_default);
        flagState = 0;
      }
      else {
        // Wait();
        stop(time_default);
        move('L', pwSlowCaribate, black_cm); // Comeback to pos
        stop(time_default);
        // stop(time_default);
        flagState = 1;
      }
      break;
    }
    if ((millis() - looptime) > check_cm) // Not Found Black
    {
      if (Pos_Robot == 0) {
        stop(time_default);
        trackLine_L(check_cm + check_diff_cm); // Comeback to pos
        stop(time_default);
        turnRight(pwTurn, encoder_turn_R);
        stop(time_default);
        Caribate('L');
        stop(time_default);
        move('R', pwSlowCaribate, black_cm);
        stop(time_default);
      }
      else {
        stop(time_default);
        trackLine_L(check_cm + check_diff_cm); // Comeback to pos
        stop(time_default);
        turnRight(pwTurn, encoder_turn_R);
        stop(time_default);

        /////////////// แก้อยู่ ////////////////
        //            Caribate('L');
        //            stop(time_default);
        //            move('R', pwSlowCaribate, black_cm);
        //            stop(time_default);
        /////////////// แก้อยู่ ////////////////
      }

      // Wait();
      movePass(pw, pass_cm, black_cm - 100);

      break;
    }
    // move('R', pw, 0);
    trackLine_R();
  }

  // Finish Function
  stop(time_default);
}
void Check_Front()
{
  // Setting
  // encoder_reset(2);
  int check_cm = check_frontblackline;
  int black_cm = return_from_caribate; // 5

  // Do
  looptime = millis();
  while (1)
  {
    // Condition
    if (S_FL < reff_FL && S_FR < reff_FR)
    {
      stop(time_default);

      Caribate('F');
      Check_Color_F();
      if (flagState != 0)
      {
        move('B', pw, black_cm - 50); // Comeback to pos
        stop(time_default);
        flagState = 2;
      }

      break;
    }

    Check_Obstacle();

    if ((millis() - looptime) > check_cm)
    {

      flagState = 0;
      break;
    }

    // Running to check
    trackLine();
    // move('F', pw, 0);
  }

  // Finish Function
  stop(time_default);
}
void Check_Left()
{
  // Setting
  // encoder_reset(2);
  int check_cm = check_blackline; // 15
  int check_diff_cm = 0;
  int black_cm = return_from_caribate;
  int pass_cm = check_frontblackline;

  // Do
  looptime = millis();
  while (1)
  {
    // Condition
    if (S_FL < reff_FL && S_BL < reff_BL) // Found Black
    {
      if (Pos_Robot == 0) {
        // Wait();
        stop(time_default);
        move('R', pwSlowCaribate, black_cm); // Comeback to pos
        stop(time_default);
        // stop(time_default);
        flagState = 1;
      }
      else {
        stop(time_default);
        Caribate('L');
        stop(time_default);
        move('R', pw, black_cm); // Comeback to pos
        stop(time_default);
        uTurn();
        stop(time_default);
        Caribate('R');
        stop(time_default);
        move('L', pwSlowCaribate, black_cm); // Comeback to pos
        stop(time_default);
        move('F', pw, pass_cm); // Comeback to pos
        stop(time_default);
        flagState = 0;
      }

      break;
    }
    if ((millis() - looptime) > check_cm) // Not Found Black
    {
      if (Pos_Robot == 1) {
        stop(time_default);
        trackLine_R(check_cm + check_diff_cm); // Comeback to pos
        stop(time_default);
        turnLeft(pwTurn, encoder_turn_L);
        stop(time_default);
        Caribate('R');
        stop(time_default);
        move('L', pwSlowCaribate, black_cm);
        stop(time_default);
      }
      else {
        stop(time_default);
        trackLine_R(check_cm + check_diff_cm); // Comeback to pos
        stop(time_default);
        turnLeft(pwTurn, encoder_turn_L);
        stop(time_default);
      }

      // moveEncoder('F', pw , pass_cm);
      movePass(pw, pass_cm, black_cm - 100);

      // flagState = 0;
      break;
    }

    // Running to Check Black Line Right Side
    // move('L',pw,1);
    trackLine_L();
  }

  // Finish Function
  stop(time_default);
}
void Check_Color_F()
{
  stop(time_check_color);
  //   while(SW_OK() == 1)
  //   {
  //       readFloorColor();
  //   }
  // Wait();
  if (getColorByRGB() == 0)
  {
    // Black
    oledClear();
    setTextSize(2);
    oled(0, 0, " Black ");
  }
  // else if (S_R > reff_S_R && S_G > reff_S_G && S_B > reff_S_B)
  // {
  //     // white
  //     oledClear();
  //     setTextSize(2);
  //     oled(0,0," White ");
  // }
  else if (getColorByRGB() == 1)
  {
    // Blue
    Do_Color('R');
  }
  else if (getColorByRGB() == 2)
  {
    // Green
    Do_Color('G');
  }
  else if (getColorByRGB() == 3)
  {
    // Red
    Do_Color('B');
  }
  else if (getColorByRGB() == 4)
  {
    // Yellow
    Do_Color('Y');
  }
  else
  {
    // No one
    oledClear();
    setTextSize(2);
    oled(0, 0, " No Color");
  }
  // Wait();
}
void Finish()
{
  // box_count >= 4
  stop(time_default);
  beep();
  beep();
  beep();
  onFlag();
  stop(30000);
  Wait();
}

// To Do
void Do_Color(char color)
{
    beep();
    oledClear();
    setTextSize(4);
    
    oled(0, 0, " %c  ", color);

    Caribate_Color();
    move('F', pwSlowCaribate, in_color);
    Box_Push(color); // Test
    Caribate_Color();
    stop(time_default);

    move('B', pw, in_color);
    uTurn();
    Caribate('B');
    // Caribate('L');
    move('F', pw, go_from_colors);
    stop(time_default);
    // Wait();
    flagState = 0; // Reset run() and all Check_... ()
}

// Check_Obstacle
void Check_Obstacle(){
    if (S_SW == 0)
    {
        move('F', pwWave, begin_obstacle);
        stop(stop_for_check);

        if (getAngleOfRobot() > reff_sapan)
        {
            Do_Sapan();
        }
        else
        {
            Do_Wave();
        }
        flagState = 0;
    }
}

// Sapan

int check_blackline_of_sapan = 520; // ค่าเดินสไลด์ซ้าย/ขวา ออกไปเพื่อเช็คเส้นดำ ของสะพาน
int flag_checksapan = 1;

void Check_Right_Sapan()
{
  // Setting
  int check_cm = check_blackline_of_sapan;
  int black_cm = return_from_caribate;

  looptime = millis();
  // Do
  while (1)
  {
    // Condition
    if (S_FR < reff_FR && S_BR < reff_BR) // Found Black
    {
        stop(time_default);
        move('L', pwSlowCaribate, black_cm); // Comeback to pos
        stop(time_default);
        break;
    }
    if ((millis() - looptime) > check_cm) // Not Found Black
    {
        stop(time_default);
        trackLine_L(check_cm); // Comeback to pos
        stop(time_default);
        turnRight(pwTurn, encoder_turn_R);
        stop(time_default);
        
        move('F', pwWave, go_down_sapan); // เดินลงสะพาน
        stop(time_default);
        flag_checksapan = 0;
      break;
    }
    trackLine_R();
  }

  // Finish Function
  stop(time_default);
}
void Check_Front_Sapan()
{
  // Setting
  int check_cm = go_down_sapan; // ค่าลงสะพาน
  int black_cm = return_from_caribate;

  // Do
  looptime = millis();
  while (1)
  {
    // Condition
    if (S_FL < reff_FL && S_FR < reff_FR) // เจอดำ
    {
      stop(time_default);

      Caribate('F');
      move('B', pw, black_cm - 50); // Comeback to pos
      stop(time_default);
      break;
    }
    if ((millis() - looptime) > check_cm)
    {
      flag_checksapan = 0;
      break;
    }

    // Running to check
    trackLine();
  }

  // Finish Function
  stop(time_default);
}
void Check_Left_Sapan()
{
  // Setting
  int check_cm = check_blackline_of_sapan;
  int black_cm = return_from_caribate;

  looptime = millis();
  // Do
  while (1)
  {
    // Condition
    if (S_FL < reff_FL && S_BL < reff_BL) // Found Black
    {
        stop(time_default);
        move('R', pwSlowCaribate, black_cm); // Comeback to pos
        stop(time_default);
        break;
    }
    if ((millis() - looptime) > check_cm) // Not Found Black
    {
        stop(time_default);
        trackLine_R(check_cm); // Comeback to pos
        stop(time_default);
        turnLeft(pwTurn, encoder_turn_L);
        stop(time_default);
        
        move('F', pwWave, go_down_sapan); // เดินลงสะพาน
        stop(time_default);
        flag_checksapan = 0;
      break;
    }
    trackLine_L();
  }

  // Finish Function
  stop(time_default);
}
void Do_Sapan()
{
    oledClear();
    oled(0, 0, "sapan!");

    move('F', pwWave, go_up_sapan);
    stop(time_default);

    while(flag_checksapan == 1){
        Check_Right_Sapan();
        Check_Front_Sapan();
        Check_Right_Sapan();
    }

}

// Wave (Ranard)
void Do_Wave()
{
    stop(time_default);
    oledClear();
    oled(0, 0, "wave!");
    move('F', pwWave, go_wave);
    stop(time_default);
}

// Normally Functionnal
void setColorSensorReff()
{
    oledClear();
    beep();
    delay(500);
    int color_value[20];
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "White Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}

    color_value[0] = S_R;
    color_value[1] = S_G;
    color_value[2] = S_B;
    oledClear();
    beep();
    delay(500);
    ////
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "Black Line");
        delay(20);
    }
    // while(SW_OK() == 0){}
    color_value[3] = S_R;
    color_value[4] = S_G;
    color_value[5] = S_B;
    oledClear();
    beep();
    delay(500);
    ////

    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "Red Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}
    color_value[6] = S_R;
    color_value[7] = S_G;
    color_value[8] = S_B;
    oledClear();
    beep();
    delay(500);
    ////
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "Green Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}
    color_value[9] = S_R;
    color_value[10] = S_G;
    color_value[11] = S_B;
    oledClear();
    beep();
    delay(500);
    ////
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "Blue Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}
    color_value[12] = S_R;
    color_value[13] = S_G;
    color_value[14] = S_B;
    oledClear();
    beep();
    delay(500);
    ////
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "Yellow Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}
    color_value[15] = S_R;
    color_value[16] = S_G;
    color_value[17] = S_B;
    oledClear();
    beep();
    delay(500);
    ////
    // Calculate
    int result_r_black = (color_value[0] + color_value[3]) / 2;
    int result_g_black = (color_value[1] + color_value[4]) / 2;
    int result_b_black = (color_value[2] + color_value[5]) / 2;
    int result_r_red = color_value[6];
    int result_g_red = color_value[7];
    int result_b_red = color_value[8];
    int result_r_green = color_value[9];
    int result_g_green = color_value[10];
    int result_b_green = color_value[11];
    int result_r_blue = color_value[12];
    int result_g_blue = color_value[13];
    int result_b_blue = color_value[14];
    int result_r_yellow = color_value[15];
    int result_g_yellow = color_value[16];
    int result_b_yellow = color_value[17];
    // Save
    EEPROM.update(startAddressColorSensor + 1, result_r_black);
    EEPROM.update(startAddressColorSensor + 2, result_g_black);
    EEPROM.update(startAddressColorSensor + 3, result_b_black);
    EEPROM.update(startAddressColorSensor + 4, result_r_red);
    EEPROM.update(startAddressColorSensor + 5, result_g_red);
    EEPROM.update(startAddressColorSensor + 6, result_b_red);
    EEPROM.update(startAddressColorSensor + 7, result_r_green);
    EEPROM.update(startAddressColorSensor + 8, result_g_green);
    EEPROM.update(startAddressColorSensor + 9, result_b_green);
    EEPROM.update(startAddressColorSensor + 10, result_r_blue);
    EEPROM.update(startAddressColorSensor + 11, result_g_blue);
    EEPROM.update(startAddressColorSensor + 12, result_b_blue);
    EEPROM.update(startAddressColorSensor + 13, result_r_yellow);
    EEPROM.update(startAddressColorSensor + 14, result_g_yellow);
    EEPROM.update(startAddressColorSensor + 15, result_b_yellow);
    

    ////
    oledClear();
    setTextSize(1);
    oled(0, 0, "Saved! ");
    Wait();
    oledClear();
}
void setMainSensorReff()
{
    oledClear();
    beep();
    delay(500);
    int color_value[14];
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Main ");
        oled(5, 20, "White Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    color_value[0] = S_FL;
    color_value[1] = S_FR;
    color_value[2] = S_BL;
    color_value[3] = S_BR;
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Main ");
        oled(5, 20, "Front Black");
        delay(20);
    }
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    color_value[4] = S_FL;
    color_value[5] = S_FR;
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Main ");
        oled(5, 20, "Back Black");
        delay(20);
    }
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    color_value[6] = S_BL;
    color_value[7] = S_BR;
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Main ");
        oled(5, 20, "Front Blue");
        delay(20);
    }
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    color_value[8] = S_FL;
    color_value[9] = S_FR;
    ////
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Main ");
        oled(5, 20, "Back Blue");
        delay(20);
    }
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    color_value[10] = S_BL;
    color_value[11] = S_BR;
    ////
    // Calculate
    int result_FL = (color_value[0] + color_value[8]) / 2;
    int result_FR = (color_value[1] + color_value[9]) / 2;
    int result_BL = (color_value[2] + color_value[10]) / 2;
    int result_BR = (color_value[3] + color_value[11]) / 2;
    int result_FL_BB = (color_value[8] + color_value[4]) / 2;
    int result_FR_BB = (color_value[9] + color_value[5]) / 2;
    // Save
    EEPROM.update(startAddressMainSensor + 1, result_FL);
    EEPROM.update(startAddressMainSensor + 2, result_FR);
    EEPROM.update(startAddressMainSensor + 3, result_BL);
    EEPROM.update(startAddressMainSensor + 4, result_BR);
    EEPROM.update(startAddressMainSensor + 5, result_FL_BB);
    EEPROM.update(startAddressMainSensor + 6, result_FR_BB);

    ////
    oledClear();
    setTextSize(1);
    oled(0, 0, 'Saved!');
    // oled(0,10,'reff_FR:%d  ',result_FR);
    // oled(0,20,'reff_BL:%d  ',result_BL);
    // oled(0,30,'reff_BR:%d  ',result_BR);
    delay(20);
    beep();
    delay(500);
    Wait();
    oledClear();
}

void ok()
{
    XIO();

    Box_Keep('R');
    Box_Keep('G');
    Box_Keep('B');
    Box_Keep('Y');
    offFlag();

    // servo(1, s1); delay(200);
    beep();
    setTextSize(2);
    while (SW_OK() == 1)
    {
        function = knob(0, 12);
        setTextSize(2);
        oled(20, 0, "Menu");
        oled(50, 20, "%d", function);
        oledClear();
        if (SW_OK() == 0)
        {
            setTextSize(1);
            oledClear();
            break;
        }
    }
    delay(200);
}
// Motor Rewrite

// Motor 1
#define Pwm1 11 // Speed control
#define InA1 15 // Direction
#define InB1 16 // Direction

// Motor 2
#define Pwm2 12 // Speed control
#define InA2 17 // Direction
#define InB2 22 // Direction

// Motor 3
#define Pwm3 13 // Speed control
#define InA3 23 // Direction
#define InB3 24 // Direction

// Motor 4
#define Pwm4 9  // Speed control
#define InA4 25 // Direction
#define InB4 26 // Direction

void Motor(char ch, int Pow)
{
    long p = 0;
    if (Pow >= -100 && Pow <= 100)
    {

        p = map(Pow, 0, 100, 0, 255);
        if (ch == 1 && Pow > 0)
        {
            pinMode(InA1, OUTPUT);
            pinMode(InB1, OUTPUT);
            pinMode(Pwm1, OUTPUT);
            digitalWrite(InA1, LOW);
            digitalWrite(InB1, HIGH);
            analogWrite(Pwm1, (int)p);
        }
        else if (ch == 1 && Pow <= 0)
        {
            pinMode(InA1, OUTPUT);
            pinMode(InB1, OUTPUT);
            pinMode(Pwm1, OUTPUT);
            digitalWrite(InA1, HIGH);
            digitalWrite(InB1, LOW);
            analogWrite(Pwm1, -(int)p);
        }
        else if (ch == 2 && Pow > 0)
        {
            pinMode(InA2, OUTPUT);
            pinMode(InB2, OUTPUT);
            pinMode(Pwm2, OUTPUT);
            digitalWrite(InA2, LOW);
            digitalWrite(InB2, HIGH);
            analogWrite(Pwm2, (int)p);
        }
        else if (ch == 2 && Pow <= 0)
        {
            pinMode(InA2, OUTPUT);
            pinMode(InB2, OUTPUT);
            pinMode(Pwm2, OUTPUT);
            digitalWrite(InA2, HIGH);
            digitalWrite(InB2, LOW);
            analogWrite(Pwm2, -(int)p);
        }
        else if (ch == 3 && Pow > 0)
        {
            pinMode(InA3, OUTPUT);
            pinMode(InB3, OUTPUT);
            pinMode(Pwm3, OUTPUT);
            digitalWrite(InA3, LOW);
            digitalWrite(InB3, HIGH);
            analogWrite(Pwm3, (int)p);
        }
        else if (ch == 3 && Pow <= 0)
        {
            pinMode(InA3, OUTPUT);
            pinMode(InB3, OUTPUT);
            pinMode(Pwm3, OUTPUT);
            digitalWrite(InA3, HIGH);
            digitalWrite(InB3, LOW);
            analogWrite(Pwm3, -(int)p);
        }
        else if (ch == 4 && Pow > 0)
        {
            pinMode(InA4, OUTPUT);
            pinMode(InB4, OUTPUT);
            pinMode(Pwm4, OUTPUT);
            digitalWrite(InA4, HIGH);
            digitalWrite(InB4, LOW);
            analogWrite(Pwm4, (int)p);
        }
        else if (ch == 4 && Pow <= 0)
        {
            pinMode(InA4, OUTPUT);
            pinMode(InB4, OUTPUT);
            pinMode(Pwm4, OUTPUT);
            digitalWrite(InA4, LOW);
            digitalWrite(InB4, HIGH);
            analogWrite(Pwm4, -(int)p);
        }
    }
}

// Debug

void test()
{
    while(S_SW == 1)
    {
        move('F', pw, 10);
    }

    move('F', pwWave, begin_obstacle);
    stop(stop_for_check);

    if(getAngleOfRobot() > reff_sapan){
        oledClear();
        setTextSize(2);
        oled(0,0,"SAPAN!! ");
        Wait();
        Sapan_L();
        Wait();
    }
    else{
        oledClear();
        setTextSize(2);
        oled(0,0,"RANARD!! ");
        Do_Wave();
    }
    Wait();
    // move('F', pw, 1000);
    // Wait();
}

