#include "sens.h"
#include <LibRobus.h>
#include <Adafruit_TCS34725.h>


#define SENS_DEBUG 1

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_MAX 0.1 //0.35
#define MOTOR_SPEED_TURN 0.25

const int SENS_COLOR_RESOLUTION = 10;

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
static Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_4X);

void sens_init()
{
    extern Adafruit_TCS34725 tcs;

    const int lineFollowSensor0 = 22;
    const int lineFollowSensor1 = 24;
    const int lineFollowSensor2 = 26;

    if (tcs.begin())
    {
        Serial.println("Found sensor");
    }
    else
    {
        Serial.println("No TCS34725 found ... please connect the color sensor");
    }

    pinMode(lineFollowSensor0, INPUT);
    pinMode(lineFollowSensor1, INPUT);
    pinMode(lineFollowSensor2, INPUT);
}

combat_color_t sens_getColor()
{
    extern Adafruit_TCS34725 tcs;

    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels

    uint16_t red, gre, blu, clear, colorTemp, lux;

    tcs.getRawData(&red, &gre, &blu, &clear);
    colorTemp = tcs.calculateColorTemperature(red, gre, blu);
    lux = tcs.calculateLux(red, gre, blu);

    int r_frac = (int)(((float)red / (uint32_t)clear) * SENS_COLOR_RESOLUTION);
    int g_frac = (int)(((float)gre / (uint32_t)clear) * SENS_COLOR_RESOLUTION);
    int b_frac = (int)(((float)blu / (uint32_t)clear) * SENS_COLOR_RESOLUTION);

    if (3 <= r_frac &&
        2 >= g_frac &&
        3 >= b_frac) //Detect RED
    {
#if SENS_DEBUG
        Serial.println("RED detected");
#endif
        return RED;
    }
    else if (2 >= r_frac &&
             3 <= g_frac &&
             3 >= b_frac &&
             12000 <= colorTemp &&
             15000 >= colorTemp) //Detect GREEN
    {
#if SENS_DEBUG
        Serial.println("GREEN detected");
#endif
        return GREEN;
    }
    else if (2 >= r_frac &&
             3 >= g_frac &&
             4 <= b_frac) //Detect BLUE
    {
#if SENS_DEBUG
        Serial.println("BLUE detected");
#endif
        return BLUE;
    }
    else if (2 <= r_frac &&
             3 <= g_frac &&
             3 >= b_frac &&
             6000 >= colorTemp) //Detect YELLOW
    {
#if SENS_DEBUG
        Serial.println("YELLOW detected");
#endif
        return YELLOW;
    }
    else
    {
#if SENS_DEBUG
        Serial.print("\t");
        Serial.print("Color Temp: ");
        Serial.print(colorTemp, DEC);
        Serial.print(" K");

        Serial.print("\t");
        Serial.print("Lux: ");
        Serial.print(lux, DEC);

        Serial.print("\t");
        Serial.print("RGB: ");
        Serial.print(red, DEC);
        Serial.print(" ");
        Serial.print(gre, DEC);
        Serial.print(" ");
        Serial.print(blu, DEC);

        Serial.print("\t");
        Serial.print("C: ");
        Serial.print(clear, DEC);

        Serial.print("\t\t#");
        Serial.print((int)r_frac, HEX);
        Serial.print((int)g_frac, HEX);
        Serial.print((int)b_frac, HEX);
        Serial.println();
#endif
        return OTHER_COLOR;
    }
}

void sens_followLineIR()
{

    // Add code from https://create.arduino.cc/projecthub/mjrobot/line-follower-robot-pid-control-android-setup-e5113a

    int error = 0;
    float Kp = 0.05;

    //The sensors name goes from "0" (more to the Left) to "2" (more to the Right)

    const int lineFollowSensor0 = 22;
    const int lineFollowSensor1 = 24;
    const int lineFollowSensor2 = 37;

    int LFSensor[3] = {0, 0, 0}; //Left to right

    LFSensor[0] = digitalRead(lineFollowSensor0);
    LFSensor[1] = digitalRead(lineFollowSensor1);
    LFSensor[2] = digitalRead(lineFollowSensor2);

    /*

    . = WHITE_NOT_LINE
    0 = BLACK_LINE
    
    . 0 0 ==> Error = 2
    . . 0 ==> Error = 1
    . 0 . ==> Error = 0
    0 . . ==> Error = -1
    0 0 . ==> Error = -2
    . . . ==> All white
    0 0 0 ==> All black

    */

#if SENS_DEBUG
    Serial.print(LFSensor[0]);
    Serial.print(" ");
    Serial.print(LFSensor[1]);
    Serial.print(" ");
    Serial.print(LFSensor[2]);
    Serial.println();
#endif

    if ((LFSensor[0] == WHITE_NOT_LINE) &&
        (LFSensor[1] == BLACK_LINE) &&
        (LFSensor[2] == BLACK_LINE))
        error = 2;
    else if ((LFSensor[0] == WHITE_NOT_LINE) &&
             (LFSensor[1] == WHITE_NOT_LINE) &&
             (LFSensor[2] == BLACK_LINE))
        error = 1;
    else if ((LFSensor[0] == WHITE_NOT_LINE) &&
             (LFSensor[1] == BLACK_LINE) &&
             (LFSensor[2] == WHITE_NOT_LINE))
        error = 0;
    else if ((LFSensor[0] == BLACK_LINE) &&
             (LFSensor[1] == WHITE_NOT_LINE) &&
             (LFSensor[2] == WHITE_NOT_LINE))
        error = -1;
    else if ((LFSensor[0] == BLACK_LINE) &&
             (LFSensor[1] == BLACK_LINE) &&
             (LFSensor[2] == WHITE_NOT_LINE))
        error = -2;
    else
    {
    }

#ifdef SENS_DEBUG
    Serial.print("\t");
    Serial.println(error);
#endif

    MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX + (Kp * error));
    MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX - (Kp * error));
}
