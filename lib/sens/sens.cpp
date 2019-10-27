#include "sens.h"
#include <LibRobus.h>
#include <Adafruit_TCS34725.h>

#define COLOR_RESOLUTION 10
#define DEBUG 1

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_4X);

void sensInitColor()
{
    static Adafruit_TCS34725 tcs;

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

sensColor_t sensGetColor()
{
    static Adafruit_TCS34725 tcs;

    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels

    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);

    int frac_r = (int)((float)r / (uint32_t)c) * COLOR_RESOLUTION;
    int frac_g = (int)((float)g / (uint32_t)c) * COLOR_RESOLUTION;
    int frac_b = (int)((float)b / (uint32_t)c) * COLOR_RESOLUTION;

    if (3 <= frac_r &&
        2 >= frac_g &&
        3 >= frac_b) //Detect RED
    {
#if DEBUG
        Serial.println("RED detected");
#endif
        return RED;
    }
    else if (2 >= frac_r &&
             3 <= frac_g &&
             3 >= frac_b) //Detect GREEN
    {
#if DEBUG
        Serial.println("GREEN detected");
#endif
        return GREEN;
    }
    else if (2 >= frac_r &&
             3 >= frac_g &&
             4 <= frac_b) //Detect BLUE
    {
#if DEBUG
        Serial.println("BLUE detected");
#endif
        return BLUE;
    }
    else if (2 <= frac_r &&
             3 <= frac_g &&
             3 >= frac_b) //Detect YELLOW
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
        Serial.print(r, DEC);
        Serial.print(" ");
        Serial.print(g, DEC);
        Serial.print(" ");
        Serial.print(b, DEC);

        Serial.print("\t");
        Serial.print("C: ");
        Serial.print(c, DEC);

        Serial.print("\t\t#");
        Serial.print((int)frac_r, HEX);
        Serial.print((int)frac_g, HEX);
        Serial.print((int)frac_b, HEX);
        Serial.println();
#endif
        return OTHER_COLOR;
    }
}
