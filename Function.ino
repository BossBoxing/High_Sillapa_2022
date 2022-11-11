// Initial Variables Port
#define S_FL map(analog(0),0,1023,0,100)
#define S_R map(analog(1),0,1023,0,255)
#define S_G map(analog(2),0,1023,0,255)
#define S_B map(analog(3),0,1023,0,255)
#define S_W map(analog(4),0,1023,0,255)
#define S_FR map(analog(5),0,1023,0,100)
#define S_BL map(analog(6),0,1023,0,100)
#define S_BR map(analog(7),0,1023,0,100)

#define Servo_R 1
#define Servo_G 2
#define Servo_B 3
#define Servo_Y 4
#define Servo_Flag 5

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

// Flag
int flagState = 0;

// Motor Control
void move(char pos, int pw, int time)
{
    if (pos == 'B')
    {
        Motor(1, -pw);  Motor(2, -pw);
        Motor(3, -pw);  Motor(4, -pw);
    }
    else if (pos == 'L')
    {
        Motor(1, -pw);  Motor(2, pw);
        Motor(3, pw);   Motor(4, -pw);
    }
    else if (pos == 'R')
    {
        Motor(1, pw);   Motor(2, -pw);
        Motor(3, -pw);  Motor(4, pw);
    }
    else
    {
        Motor(1, pw);   Motor(2, pw);
        Motor(3, pw);   Motor(4, pw);
    }
    delay(time);
}
void turnLeft(int pw, int time)
{
    Motor(1, -pw);  Motor(2, pw);
    Motor(3, -pw);  Motor(4, pw);
    delay(time);
}
void turnRight(int pw, int time)
{
    Motor(1, pw);   Motor(2, -pw);
    Motor(3, pw);   Motor(4, -pw);
    delay(time);
}
void stop(int time)
{
    Motor(1, 0);    Motor(2, 0);
    Motor(3, 0);    Motor(4, 0);
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
        for (int i = Servo_G_Keep; i > Servo_G_Push; i-=1)
        {
            /* code */
            servo(Servo_G, i);
            delay(10);
        }
    }
    else if (color == 'B')
    {
        // servo(Servo_B, Servo_B_Push);
        for (int i = Servo_B_Keep; i > Servo_B_Push; i-=1)
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
    if(box_count >= 4){Finish();}
}

// Encoder Motor Control
void moveEncoderPure(char pos, int pw, int cm)
{
    stop(200);
    if (pos == 'B')
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            move('B', pw, 1);
        }
    }
    else if (pos == 'L')
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            move('L', pw, 1);
        }
    }
    else if (pos == 'R')
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            move('R', pw, 1);
        }
    }
    else
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            // trackLine();
            move('F', pw, 1);
        }
    }
    stop(200);
}
void moveEncoder(char pos, int pw, int cm)
{
    stop(200);
    if (pos == 'B')
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            move('B', pw, 1);
        }
    }
    else if (pos == 'L')
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            move('L', pw, 1);
        }
    }
    else if (pos == 'R')
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            move('R', pw, 1);
        }
    }
    else
    {
        encoder_reset(3);
        int Cm = (cm / 0.28);
        while (encoder(3) < Cm)
        {
            trackLine();
            // move('F', pw, 1);
        }
    }
    stop(200);
}
void turnLeftEncoder(int bit)
{
    stop(time_default);
    encoder_reset(3);
    while(encoder(3) < bit){
        turnLeft(pwTurn,1);
    }
    stop(time_default);
}
void turnRightEncoder(int bit)
{
    stop(time_default);
    encoder_reset(2);
    while(encoder(2) < bit){
        turnRight(pwTurn,1);
    }
    stop(time_default);
}
void uTurn(){
    turnRightEncoder(encoder_turn_U);
}

// TrackLine
void turnLeftTrack()
{
    Motor(1, 5);  Motor(2, pw);
    Motor(3, 5);  Motor(4, pw);
    delay(10);
}
void turnRightTrack()
{
    Motor(1, pw);   Motor(2, 5);
    Motor(3, pw);   Motor(4, 5);
    delay(10);
}
void trackLine() // Used on moveEncoder('F')
{
    if (S_FL < reff_FL && S_FR > reff_FR
    && S_R > reff_S_R && S_B > reff_S_B)
    {
        // Normal Track
        // TR
        turnRightTrack();
    }
    else if (S_FL > reff_FL && S_FR < reff_FR
    && S_R > reff_S_R && S_B > reff_S_B)
    {
        // Normal Track
        // TL
        turnLeftTrack();
    }
    else if (S_FL < reff_FL)
    {
        // Found Black Track
        // TL
        turnLeft(pwSlowCaribate, 1);
        // turnLeftTrack();
    }
    else if (S_FR < reff_FR)
    {
        // Found Black Track
        // TR
        turnRight(pwSlowCaribate, 1);
        // turnRightTrack();
    }
    else
    {
        move('F',pw,10);
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
        move('R',pw,10);
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
        move('L',pw,10);
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
    oled(50, 30, "White:%d ", S_W);
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
    oled(0, 30, "W: %d ", S_W);
    delay(100);
    oledClear();
}
void readEncoder()
{

    encoder_reset(2);
    encoder_reset(3);

    while (1)
    {
        oled(0, 0, "en(2) : %d  ", encoder(2));
        oled(0, 10, "en(3) : %d  ", encoder(3));
        delay(100);
        oledClear();
    }
}
void Wait(){
    stop(time_default);
    beep();
    while(SW_OK() == 1){}
    while(SW_OK() == 0){}
    beep();
}

// Caribate for Straight
void Caribate(char pos)
{
    if (pos == 'L')
    {
        moveEncoder('R',pwSlowCaribate,5);
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
        moveEncoder('L',pwSlowCaribate,5);
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
            move('R',pwSlowCaribate,10);
        }
        move('R',pwSlowCaribate,50);
    }
    else if (pos == 'B')
    {
        moveEncoder('F',pwSlowCaribate,3);
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
        moveEncoder('B',pwSlowCaribate,3);
        while (S_FL > reff_FL || S_FR > reff_FR)
        {
            if (S_FL < reff_FL)
            {
                turnLeft(pwSlowCaribate, 1);
            }
            else if (S_FR < reff_FR)
            {
                turnRight(pwSlowCaribate, 1);
            }
            else
            {
                move('F', pwSlowCaribate, 1);
            }
        }
        stop(30);
        moveEncoder('F', pwSlowCaribate, 0.9);
        stop(30);
    }
    stop(300);
}
void Caribate_Color(){
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
void movePass(int pw, int cm, int black_cm)
{
    stop(200);

    encoder_reset(3);
    int Cm = (cm / 0.28);
    while (encoder(3) < Cm)
    {
        if (S_FL < reff_FL && S_FR < reff_FR)
        {
            // Found Black Line ????
            // stop(1000);
            // oledClear();
            // oled(0,0,"%d ",);
            // stop(1000);
            // Wait();
            if (S_R < reff_S_R && S_G < reff_S_G && S_B < reff_S_B)
            {
                Caribate('F');
                moveEncoder('B', pw, 15);
                turnLeftEncoder(encoder_turn_L);
                // flagState=2;
            }
            else
            {
                Caribate('F');
                moveEncoder('B', pw, black_cm);
            }
            flagState=1;
            break;
        }
        trackLine();
        // move('F', pw, 1);
    }

    stop(200);
}

// Algorithm
int getEncoderCentimater(int cm)
{
    return (cm / 0.28);
}

// Pattern
void run()
{
    if (flagState == 0)
        {Check_Right();}
    else if (flagState == 1)
        {Check_Front();}
    else if (flagState == 2)
        {Check_Left();}

}
void Check_Right()
{
    // Setting
    encoder_reset(3);
    int check_cm = check_blackline;
    int check_diff_cm = 0;
    int black_cm = return_from_caribate;
    int pass_cm = check_frontblackline;

    // Do
    while(1)
    {
        // Condition
        if (S_FR < reff_FR && S_BR < reff_BR) // Found Black
        {
            Caribate('R');
            moveEncoder('L', pwSlowCaribate , black_cm); // Comeback to pos
            flagState = 1;
            break;
        }
        if (encoder(3) > getEncoderCentimater(check_cm)) // Not Found Black
        {
            moveEncoder('L', pw , check_cm + check_diff_cm); // Comeback to pos
            turnRightEncoder(encoder_turn_R);
            
            // moveEncoder('F', pw , pass_cm);
            movePass(pw ,pass_cm, black_cm);
            
            break;
        }

        // Running to Check Black Line Right Side
            // move('R',pw,1);
        trackLine_R();
    }

    // Finish Function
    stop(time_default);
}
void Check_Front()
{
    // Setting
    encoder_reset(3);
    int check_cm = check_frontblackline;
    int black_cm = return_from_caribate; // 5

    // Do
    while (1)
    {
        // Condition
        if (S_FL < reff_FL &&  S_FR < reff_FR)
        {
            // Wait();
            stop(time_default);

            Caribate('F');
            Check_Color_F();
            if(flagState != 0){
                moveEncoder('B', pw , black_cm); // Comeback to pos
                flagState=2;
            }
            
            break;
            
        }
        if (encoder(3) > getEncoderCentimater(check_cm) )
        {
            stop(time_default);
            flagState=0;
            break;
        }

        // Running to check
        move('F', pw, 1);
    }

    // Finish Function
    stop(time_default);
}
void Check_Left()
{
    // Setting
    encoder_reset(3);
    int check_cm = check_blackline; // 15
    int check_diff_cm = 0;
    int black_cm = return_from_caribate;
    int pass_cm = check_frontblackline;

    // Do
    while(1)
    {
        // Condition
        if (S_FL < reff_FL && S_BL < reff_BL) // Found Black
        {
            Caribate('L');
            moveEncoder('R', pw , black_cm); // Comeback to pos
            uTurn();
            Caribate('R');
            moveEncoder('L', pwSlowCaribate , black_cm); // Comeback to pos
            moveEncoder('F', pw , pass_cm); // Comeback to pos
            flagState=0;
            break;
        }
        if (encoder(3) > getEncoderCentimater(check_cm)) // Not Found Black
        {
            stop(time_default);
            moveEncoder('R', pw , check_cm + check_diff_cm); // Comeback to pos
            turnLeftEncoder(encoder_turn_L);
            Caribate('R');
            moveEncoder('L', pwSlowCaribate , black_cm);
            
            // moveEncoder('F', pw , pass_cm);
            movePass(pw ,pass_cm, black_cm);

            flagState=0;
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
    // Wait();
    if (S_R < reff_S_R && S_G < reff_S_G && S_B < reff_S_B)
    {
        // Black
        // oledClear();
        // setTextSize(2);
        // oled(0,0," Black ");
    }
    else if (S_R > reff_S_R && S_G > reff_S_G && S_B > reff_S_B)
    {
        // white
        // oledClear();
        // setTextSize(2);
        // oled(0,0," White ");
    }
    else if (S_B > S_R && S_B > S_G)
    {
        // Blue
        Do_Color('B');
    }
    else if (S_G > S_R && S_G > S_B)
    {
        // Green
        Do_Color('G');
    }
    else if (S_R > S_B && S_G < reff_S_G_RY)
    {
        // Red
        Do_Color('R');
    }
    else if (S_R > S_B && S_G > reff_S_G_RY)
    {
        // Yellow
        Do_Color('Y');
    }
    else
    {
        // No one
        // oledClear();
        // setTextSize(2);
        // oled(0,0," Else! No Color No Black ");
    }
    // Wait();
}
void Check_Finish()
{
    // if All Box Push on The Color Field
    // Do
    // Servo On Flag
    // And Stop the Robot
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
    oled(0,0," %s  " , color);

    Caribate_Color();
    moveEncoderPure('F',pwSlowCaribate,3);
    Box_Push(color); // Test
    Caribate_Color();
    stop(1000);

    moveEncoder('B', pw, 3);
    uTurn();
    Caribate('B');
    // Caribate('L');
    moveEncoder('F', pw, 18);
    stop(time_default);
    // Wait();
    flagState = 0; // Reset run() and all Check_... ()
}

// Normally Functionnal
void setColorSensorReff()
{
    oledClear();
    beep();
    delay(500);
    int color_value[10];
    setTextSize(2);
    delay(500);
    while (SW_OK() == 1)
    {
        oled(10, 0, " Color ");
        oled(5, 20, "White Floor");
        delay(20);
    }
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    color_value[0] = S_R;
    color_value[1] = S_G;
    color_value[2] = S_B;
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
    oledClear();
    beep();
    delay(500);
    ////
    color_value[3] = S_R;
    color_value[4] = S_G;
    color_value[5] = S_B;
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
    oledClear();
    beep();
    delay(500);
    ////
    color_value[6] = S_G;
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
    oledClear();
    beep();
    delay(500);
    ////
    color_value[7] = S_G;
    ////
    // while(SW_OK() == 0){}
    oledClear();
    beep();
    delay(500);
    ////
    // Calculate
    int result_red = (color_value[0] + color_value[3]) / 2;
    int result_green = (color_value[1] + color_value[4]) / 2;
    int result_blue = (color_value[2] + color_value[5]) / 2;
    int result_redyellow = (color_value[6] + color_value[7]) / 2;
    // Save
    EEPROM.update(startAddressColorSensor + 1, result_red);
    EEPROM.update(startAddressColorSensor + 2, result_green);
    EEPROM.update(startAddressColorSensor + 3, result_blue);
    EEPROM.update(startAddressColorSensor + 4, result_redyellow);

    ////
    setTextSize(1);
    oled(0,0,'reff_R:%d  ',result_red);
    oled(0,10,'reff_G:%d  ',result_green);
    oled(0,20,'reff_B:%d  ',result_blue);
    oled(0,30,'reff_RY:%d  ',result_redyellow);
    delay(20);
    beep();
    delay(500);
    Wait();
    oledClear();
}
void setMainSensorReff()
{
    oledClear();
    beep();
    delay(500);
    int color_value[10];
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
        oled(5, 20, "Front Blue");
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
        oled(5, 20, "Back Blue");
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
    // Calculate
    int result_FL = (color_value[0] + color_value[4]) / 2;
    int result_FR = (color_value[1] + color_value[5]) / 2;
    int result_BL = (color_value[2] + color_value[6]) / 2;
    int result_BR = (color_value[3] + color_value[7]) / 2;
    // Save
    EEPROM.update(startAddressMainSensor + 1, result_FL);
    EEPROM.update(startAddressMainSensor + 2, result_FR);
    EEPROM.update(startAddressMainSensor + 3, result_BL);
    EEPROM.update(startAddressMainSensor + 4, result_BR);

    ////
    oledClear();
    setTextSize(1);
    oled(0,0,'reff_FL:%d  ',result_FL);
    oled(0,10,'reff_FR:%d  ',result_FR);
    oled(0,20,'reff_BL:%d  ',result_BL);
    oled(0,30,'reff_BR:%d  ',result_BR);
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
    setTextSize(2);
    while (SW_OK() == 1)
    {
        function = knob(0, 5);
        setTextSize(2);
        oled(20,0,"Menu");
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
