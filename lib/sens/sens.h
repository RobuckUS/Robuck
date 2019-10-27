#ifndef SENS_H_
#define SENS_H_

#define sensColorNameMASK = 0x03;    //0b 0000 0011
#define sensColorInvalidMask = 0x80; //0b 1000 0000

typedef enum
{                  //0b ???? ??xy
    RED = 0x00,    //0b 0000 0000
    GREEN = 0x01,  //0b 0000 0001
    BLUE = 0x03,   //0b 0000 0011
    YELLOW = 0x02, //0b 0000 0010
    WHITE,
    BLACK,
    OTHER_COLOR = 0xFF, //0b 1111 1111

    // +-----+    +-------+
    // |G   B|    |01   11|
    // |     | => |       |
    // |R   Y|    |00   10|
    // +-----+    +-------+

} sensColor_t;

void sensInitColor();
sensColor_t sensGetColor();

#endif
