#include "sens.h"
#include <LibRobus.h>
#include <Adafruit_TCS34725.h>

#define DEBUG 1
#define COLOR_RESOLUTION 10

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_4X);

void sensInitColor()
{
    extern Adafruit_TCS34725 tcs;

    if (tcs.begin())
    {
        Serial.println("Found sensor");
    }
    else
    {
        Serial.println("No TCS34725 found ... check your connections");
        while (1)
            ; // halt!
    }
}

coreColor_t sensGetColor()
{
    extern Adafruit_TCS34725 tcs;

    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels

    uint16_t red, gre, blu, clear, colorTemp, lux;

    tcs.getRawData(&red, &gre, &blu, &clear);
    colorTemp = tcs.calculateColorTemperature(red, gre, blu);
    lux = tcs.calculateLux(red, gre, blu);

    int r_frac = (int)(((float)red / (uint32_t)clear) * COLOR_RESOLUTION);
    int g_frac = (int)(((float)gre / (uint32_t)clear) * COLOR_RESOLUTION);
    int b_frac = (int)(((float)blu / (uint32_t)clear) * COLOR_RESOLUTION);

    if (3 <= r_frac &&
        2 >= g_frac &&
        3 >= b_frac) //Detect RED
    {
#if DEBUG
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
#if DEBUG
        Serial.println("GREEN detected");
#endif
        return GREEN;
    }
    else if (2 >= r_frac &&
             3 >= g_frac &&
             4 <= b_frac) //Detect BLUE
    {
#if DEBUG
        Serial.println("BLUE detected");
#endif
        return BLUE;
    }
    else if (2 <= r_frac &&
             3 <= g_frac &&
             3 >= b_frac &&
             6000 >= colorTemp) //Detect YELLOW
    {
#if DEBUG
        Serial.println("YELLOW detected");
#endif
        return YELLOW;
    }
    else
    {
#if DEBUG
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
