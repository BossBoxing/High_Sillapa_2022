// Initial Variables Port
#define S_L_B analog(4)
#define S_L_R analog(5)
#define S_L_G analog(6)
#define S_R_B analog(7)
#define S_R_R analog(8)
#define S_R_G analog(9)
#define S_R map(analog(0),0,1023,0,255)
#define S_G map(analog(1),0,1023,0,255)
#define S_B map(analog(2),0,1023,0,255)
#define S_W map(analog(3),0,1023,0,255)

// Reference Main Sensor
int reff_L_R = 372;
int reff_L_G = 731;
int reff_L_B = 731;
int reff_R_R = 331;
int reff_R_G = 773;
int reff_R_B = 773;

// for Check Color Side
int reff_R_G_RY = 535;
int reff_L_B_BB = 410;
int reff_R_B_BB = 481;

// Reference Color Sensor
int reff_S_R = 130;
int reff_S_G = 130;
int reff_S_B = 130;
int reff_S_G_RY = 140;

#define Servo_R 1
#define Servo_G 2
#define Servo_B 3
#define Servo_Y 4
#define Servo_Flag 5

int Servo_R_Keep = 120;
int Servo_R_Push = 120;
int Servo_G_Keep = 120;
int Servo_G_Push = 120;
int Servo_B_Keep = 176; // Test
int Servo_B_Push = 116; // Test
int Servo_Y_Keep = 120;
int Servo_Y_Push = 120;
int Servo_Flag_Off = 120;
int Servo_Flag_On = 120;

#define E_FL 1
#define E_FR 2
#define E_BL 18
#define E_BR 19

int pw = 35;
int pwSlow = 25;
int pwTurn= 40;
int pwSlowCaribate = 20;
int time_default = 100;

int encoder_turn_L = 71;
int encoder_turn_R = 68;
int encoder_turn_U = 142;

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
     stop(100);
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
    delay(400);
}

// Encoder Motor Control
void moveEncoder(char pos, int pw, int cm)
{
    stop(100);
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
}
void turnLeftEncoder(int bit)
{
    stop(100);
    encoder_reset(3);
    while(encoder(3) < bit){
        turnLeft(pwTurn,1);
    }
    stop(100);
}
void turnRightEncoder(int bit)
{
    stop(100);
    encoder_reset(2);
    while(encoder(2) < bit){
        turnRight(pwTurn,1);
    }
    stop(100);
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
    if (S_L_B < reff_L_B && S_R_B > reff_R_B)
    {
        // TR
        turnRightTrack();
    }
    else if (S_L_B > reff_L_B && S_R_B < reff_R_B)
    {
        // TL
        turnLeftTrack();
    }
    else
    {
        move('F',pw,10);
    }
}

// Functionally for test
void readSensor()
{
    // oled(0, 0, "FL:%d ", S_FL);
    // oled(0, 10, "FR:%d ", S_FR);
    // oled(0, 20, "BL:%d ", S_BL);
    // oled(0, 30, "BR:%d ", S_BR);
    // oled(50, 0, "Red:%d ", S_R);
    // oled(50, 10, "Green:%d ", S_G);
    // oled(50, 20, "Blue:%d ", S_B);
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
    stop(100);
    beep();
    while(SW_OK() == 1){}
    while(SW_OK() == 0){}
    beep();
}
void readMainSensor(){
    oled(0,0,"Left_R: %d ",S_L_R);
    oled(0,10,"Left_G: %d ",S_L_G);
    oled(0,20,"Left_B: %d ",S_L_B);
    oled(0,30,"Right_R: %d ",S_R_R);
    oled(0,40,"Right_G: %d ",S_R_G);
    oled(0,50,"Right_B: %d ",S_R_B);
    delay(100);
    oledClear();
}

// Caribate for Straight
void Caribate(char pos)
{
    if (pos == 'L')
    {
        moveEncoder('R',pwSlowCaribate,4);
        while (S_L_B > reff_L_B || S_L_G > reff_L_G)
        {
            if (S_L_B < reff_L_B)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else if (S_L_G < reff_L_G)
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
        while (S_R_B > reff_R_B || S_R_G > reff_R_G)
        {
            if (S_R_B < reff_R_B)
            {
                turnLeft(pwSlowCaribate, 10);
            }
            else if (S_R_G < reff_R_G)
            {
                turnRight(pwSlowCaribate, 10);
            }
            else
            {
                move('R', pwSlowCaribate, 10);
            }
        }
        stop(30);
        while (S_R_B > reff_R_B || S_R_G > reff_R_G)
        {
            move('R',pwSlowCaribate,10);
        }
        move('R',pwSlowCaribate,50);
    }
    else if (pos == 'B')
    {
        moveEncoder('F',pwSlowCaribate,4);
        while (S_L_G > reff_L_G || S_R_G > reff_R_G)
        {
            if (S_L_G < reff_L_G)
            {
                turnRight(pwSlowCaribate, 1);
            }
            else if (S_R_G < reff_R_G)
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
        while (S_L_B > reff_L_B || S_R_B > reff_R_B)
        {
            if (S_L_B < reff_L_B)
            {
                turnLeft(pwSlowCaribate, 1);
            }
            else if (S_R_B < reff_R_B)
            {
                turnRight(pwSlowCaribate, 1);
            }
            else
            {
                move('F', pwSlowCaribate, 1);
            }
        }
        stop(30);
        moveEncoder('F', pwSlowCaribate, 1);
        stop(30);
    }
    stop(300);
}
void Caribate_Color(){
    // moveEncoder('R',pwSlowCaribate,4);
    while (S_L_B < reff_L_B || S_R_B < reff_R_B)
    {
        if (S_L_B > reff_L_B)
        {
            turnRight(pwSlowCaribate, 10);
        }
        else if (S_R_B > reff_R_B)
        {
            turnLeft(pwSlowCaribate, 10);
        }
        else
        {
            move('B', pwSlowCaribate, 10);
        }
    }
    stop(100);
}

// Algorithm
int getEncoderCentimater(int cm)
{
    return (cm / 0.28);
}

// Pattern
int flagState = 0;
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
    int check_cm = 10;
    int black_cm = 5;
    int pass_cm = 29;

    // Do
    while(1)
    {
        // Condition
        if (S_R_B < reff_R_B && S_R_G < reff_R_G) // Found Black
        {
            Caribate('R');
            moveEncoder('L', pw , black_cm); // Comeback to pos
            flagState = 1;
            break;
        }
        if (encoder(3) > getEncoderCentimater(check_cm)) // Not Found Black
        {
            moveEncoder('L', pw , check_cm); // Comeback to pos
            turnRightEncoder(encoder_turn_R);
            moveEncoder('F', pw , pass_cm);
            break;
        }

        // Running to Check Black Line Right Side
        move('R',pw,1);
    }

    // Finish Function
    stop(100);
}
void Check_Front()
{
    // Setting
    encoder_reset(3);
    int check_cm = 29;
    int black_cm = 5;

    // Do
    while (1)
    {
        // Condition
        if (S_L_B < reff_L_B &&  S_R_B < reff_R_B)
        {
            stop(100);

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
            stop(100);
            flagState=0;
            break;
        }

        // Running to check
        move('F', pw, 1);
    }

    // Finish Function
    stop(100);
}
void Check_Left()
{
    // Setting
    encoder_reset(3);
    int check_cm = 10;
    int black_cm = 5;
    int pass_cm = 29;

    // Do
    while(1)
    {
        // Condition
        if (S_L_B < reff_L_B && S_L_G < reff_L_G) // Found Black
        {
            Caribate('L');
            moveEncoder('R', pw , black_cm); // Comeback to pos
            uTurn();
            Caribate('R');
            moveEncoder('L', pw , black_cm); // Comeback to pos
            moveEncoder('F', pw , pass_cm); // Comeback to pos
            flagState=0;
            break;
        }
        if (encoder(3) > getEncoderCentimater(check_cm)) // Not Found Black
        {
            stop(100);
            moveEncoder('R', pw , check_cm); // Comeback to pos
            turnLeftEncoder(encoder_turn_L);
            Caribate('R');
            moveEncoder('L', pw , black_cm); // Comeback to pos
            moveEncoder('F', pw , pass_cm); // Comeback to pos
            flagState=0;
            break;
        }

        // Running to Check Black Line Right Side
        move('L',pw,1);
    }

    // Finish Function
    stop(100);
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

// To Do
void Do_Color(char color)
{
    beep();
    oledClear();
    setTextSize(4);
    oled(0,0," %s  " , color);

    Caribate_Color();
    moveEncoder('F',pwSlowCaribate,3);
    Box_Push(color); // Test
    Caribate_Color();
    stop(1000);

    moveEncoder('B', pw, 3);
    uTurn();
    Caribate('B');
    // Caribate('L');
    moveEncoder('F', pw, 18);
    stop(100);
    Wait();
    flagState = 0; // Reset run() and all Check_... ()
}
// Normally Functionnal
void ok()
{
    XIO();
    Box_Keep('B');
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
