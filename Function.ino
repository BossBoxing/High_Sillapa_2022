#define S_FL analog(0)
#define S_FR analog(5)
#define S_R analog(1)
#define S_G analog(2)
#define S_B analog(3)
#define S_W analog(4)
#define S_BL analog(6)
#define S_BR analog(7)

int reff_S_FL = 424;
int reff_S_FR = 321;
int reff_S_BL = 710;
int reff_S_BR = 510;

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

int pw = 51;
int pwSlow = 30;
int pwTurn= 45;
int pwSlowCaribate = 30;
int time_default = 100;

int encoder_turn_L = 68;
int encoder_turn_R = 68;

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
        Motor(1, pw);
        Motor(2, pw);
        Motor(3, pw);
        Motor(4, pw);
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
    if (color == 'R')
    {
        servo(Servo_R, Servo_R_Push);
    }
    else if (color == 'G')
    {
        servo(Servo_G, Servo_G_Push);
    }
    else if (color == 'B')
    {
        servo(Servo_B, Servo_B_Push);
    }
    else
    {
        servo(Servo_Y, Servo_Y_Push);
    }
    delay(time_default);
}

// Encoder Motor Control
void moveEncoder(char pos, int pw, int cm)
{
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
            move('F', pw, 1);
        }
    }
}
void turnLeftEncoder(int bit)
{
    encoder_reset(3);
    while(encoder(3) < bit){
        turnLeft(pwTurn,1);
    }
    stop(100);
}
void turnRightEncoder(int bit)
{
    encoder_reset(2);
    while(encoder(2) < bit){
        turnRight(pwTurn,1);
    }
    stop(100);
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
        p = knob(1, 4);
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
    oled(0, 0, "R: %d ", map(S_R, 0, 1023, 0, 255));
    oled(0, 10, "G: %d ", map(S_G, 0, 1023, 0, 255));
    oled(0, 20, "B: %d ", map(S_B, 0, 1023, 0, 255));
    oled(0, 30, "W: %d ", map(S_W, 0, 1023, 0, 255));
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

// Caribate for Straight
void Caribate(char pos)
{
    if (pos == 'L')
    {
        moveEncoder('R',pwSlowCaribate,4);
        while (S_FL > reff_S_FL || S_BL > reff_S_BL)
        {
            if (S_FL <= reff_S_FL)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else if (S_BL <= reff_S_BL)
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
        moveEncoder('L',pwSlowCaribate,4);
        while (S_FR > reff_S_FR || S_BR > reff_S_BR)
        {
            if (S_FR <= reff_S_FR)
            {
                turnLeft(pwSlowCaribate, 10);
            }
            else if (S_BR <= reff_S_BR)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else
            {
                move('R', pwSlowCaribate, 10);
            }
        }
    }
    else if (pos == 'B')
    {
        moveEncoder('F',pwSlowCaribate,4);
        while (S_BL > reff_S_BL || S_BR > reff_S_BR)
        {
            if (S_BL < reff_S_BL)
            {
                turnRight(pwSlowCaribate, 1);
            }
            else if (S_BR < reff_S_BR)
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
        moveEncoder('B',pwSlowCaribate,4);
        while (S_FL > reff_S_FL || S_FR > reff_S_FR)
        {
            if (S_FL <= reff_S_FL)
            {
                turnLeft(pwSlowCaribate, 1);
            }
            else if (S_FR <= reff_S_FR)
            {
                turnRight(pwSlowCaribate, 1);
            }
            else
            {
                move('F', pwSlowCaribate, 1);
            }
        }
    }
    stop(100);
}

// Algorithm
// Pattern
int flagState = 0;
void run(char side)
{
    if(side == 'L'){
        flagState = 0;
    if (flagState == 0)
        Check_Left(side);
    if (flagState == 1)
        Check_Front();
    if (flagState == 2)
        Check_Right(side);
    }
    else{
        flagState = 0;
    if (flagState == 0)
        Check_Right(side);
    if (flagState == 1)
        Check_Front();
    if (flagState == 2)
        Check_Left(side);
    }
}
void Check_Left(char side)
{
    encoder_reset(3);

    int cm = 28;
    int Cm = (cm / 0.28);
    while (1)
    {
        if (S_FL < reff_S_FL || S_BL < reff_S_BL)
        {
            // Found Black Line
            stop(100);
            Caribate('L');
            moveEncoder('R', pw, 5);
            stop(100);
            if(side == 'L'){flagState=1;}
            else{flagState=3;}
            break;
        }
        if (encoder(3) > Cm)
        {
            stop(100);
            turnLeftEncoder(encoder_turn_L);
            break;
        }
        move('L', pw, 1);
    }
}
void Check_Right(char side)
{
    encoder_reset(3);

    int cm = 28;
    int Cm = (cm / 0.28);
    while (1)
    {
        if (S_FR < reff_S_FR || S_BR < reff_S_BR)
        {
            // Found Black Line
            stop(100);
            Caribate('R');
            moveEncoder('L', pw, 5);
            stop(100);
            if(side == 'L'){flagState=3;}
            else{flagState=1;}
            break;
        }
        if (encoder(3) < Cm)
        {
            stop(100);
            turnRightEncoder(encoder_turn_R);
            break;
        }
        move('R', pw, 1);
    }
}
void Check_Front()
{
    encoder_reset(3);

    int cm = 28;
    int Cm = (cm / 0.28);
    while (encoder(3) < Cm)
    {
        if (S_FL < reff_S_FL || S_FR < reff_S_FR)
        {
            // Found Black Line
            stop(100);
            Caribate('F');
            moveEncoder('B', pw, 5);
            stop(100);
            flagState=2;
            break;
        }
        move('F', pw, 1);
    }
    stop(100);
}
void Check_Color_Floor()
{
    // if (color == 'R'){
    //     // Servo R On
    // }
    // else if (color == 'G'){
    //     // Servo G On
    // }
    // else if (color == 'B'){
    //     // Servo B On
    // }
    // else{ // Y
    //     // Servo Y On
    // }
}
void Check_Finish()
{
    // if All Box Push on The Color Field
    // Do
    // Servo On Flag
    // And Stop the Robot
}

// To Do
void Go_Forward()
{
}
void Go_Left()
{
}
void Go_Right()
{
}
void Go_Backward()
{
}

// Normally Functionnal
void ok()
{
    XIO();
    // servo(1, s1); delay(200);
    setTextSize(1);
    while (SW_OK() == 1)
    {
        function = knob(0, 5);
        setTextSize(5);
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
