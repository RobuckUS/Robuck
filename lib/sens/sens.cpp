#include "sens.h"
#include <LibRobus.h>
#include <Adafruit_TCS34725.h>

#define SENS_DEBUG 1
const int SENS_COLOR_RESOLUTION = 10;

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
static Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_4X);

void sens_init()
{
    extern Adafruit_TCS34725 tcs;

    if (tcs.begin())
    {
        Serial.println("Found sensor");
    }
    else
    {
        Serial.println("No TCS34725 found ... please connect the color sensor");
        while (1)
            ; // halt!
    }
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

    int error;

    const int lineFollowSensor0 = 22;
    const int lineFollowSensor1 = 24;
    const int lineFollowSensor2 = 26;

    int LFSensor[3] = {0, 0, 0};

    LFSensor[0] = digitalRead(lineFollowSensor0);
    LFSensor[1] = digitalRead(lineFollowSensor1);
    LFSensor[2] = digitalRead(lineFollowSensor2);

    /*
    0 0 1 ==> Error = 2
    0 1 1 ==> Error = 1
    0 1 0 ==> Error = 0
    1 1 0 ==> Error = -1
    1 0 0 ==> Error = -2
    */

#if SENS_DEBUG
    Serial.print(LFSensor[0]);
    Serial.print(" ");
    Serial.print(LFSensor[1]);
    Serial.print(" ");
    Serial.print(LFSensor[2]);
    Serial.println();
#endif

    if ((LFSensor[0] == 0) &&
        (LFSensor[1] == 0) &&
        (LFSensor[2] == 1))
        error = 2;
    else if ((LFSensor[0] == 0) &&
             (LFSensor[1] == 1) &&
             (LFSensor[2] == 1))
        error = 1;
    else if ((LFSensor[0] == 0) &&
             (LFSensor[1] == 1) &&
             (LFSensor[2] == 0))
        error = 0;
    else if ((LFSensor[0] == 1) &&
             (LFSensor[1] == 1) &&
             (LFSensor[2] == 0))
        error = -1;
    else if ((LFSensor[0] == 1) &&
             (LFSensor[1] == 0) &&
             (LFSensor[2] == 0))
        error = -2;

    else
    {
        error = 0;
        AX_BuzzerON();
        delay(200);
        AX_BuzzerOFF();
        delay(50);
    }

    float Kp = 0.05;
    MOTOR_SetSpeed(LEFT, 0.1 + (Kp * error));
    MOTOR_SetSpeed(RIGHT, 0.1 - (Kp * error));
}
