#include "motor.h"

#define DIR_FORWARD 0
#define DIR_LEFT

/** Function to control the two DC motors on robots

@param speed, reprensents direction and amplitude of PWM
floating value between [-1.0, 1.0]
*/
void motor_walk(float speed)
{
    MOTOR_SetSpeed(LEFT,speed);
    MOTOR_SetSpeed(RIGHT,speed);
}

void motor_turn(float direction, float speed)
{
    //TODO
}
