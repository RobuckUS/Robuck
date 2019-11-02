#ifndef SENS_H_
#define SENS_H_

#include <combat.h>

void sens_init();
combat_color_t sens_getColor();
void sens_followLineIR();

typedef enum
{
    BLACK_LINE = 0,
    WHITE_NOT_LINE = 1,

} combat_line_color_t;

#endif
