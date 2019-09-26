#include <LibRobus.h>

#include "motor.h"

#define DIR_FORWARD 0

#if 0
#define DIR_LEFT //TODO
#endif

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_DEBUG 0.1
#define MOTOR_SPEED_MAX MOTOR_SPEED_DEBUG

int32_t cm2pulse(float cm);

/** Function to control the two DC motors on robots
 * 
 * @param distance, reprensents direction and distance of the robot.
 * floating value in centimer between [-1.0, 1.0]
*/
void motor_walk(float distance)
{
    //init motor_walk
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int32_t goal = cm2pulse(distance);
    bool b_done_left = false;
    bool b_done_right = false;

    //loop motor_walk
    while (!(b_done_left && b_done_right))
    {
        if (ENCODER_Read(LEFT) < goal)
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
            b_done_left = true;
        }

        if (ENCODER_Read(RIGHT) < goal)
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
            b_done_right = true;
        }
    }

    Serial.println(ENCODER_Read(LEFT));
    Serial.println(ENCODER_Read(RIGHT));
    Serial.println("\n");

    //MOTOR_SetSpeed(LEFT,speed);
    //MOTOR_SetSpeed(RIGHT,speed);
}

/** Function to control the two DC motors on robots
 * 
 * @param angle, reprensents the angle of the robot relative to it direction and distance of the robot.
 * floating value in degree between [-1.0, 1.0]
*/
void motor_turn(float angle)
{
    //init motor_walk
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int32_t goal = cm2pulse(angle);
    bool b_done_left = false;
    bool b_done_right = false;

    //loop motor_walk
    while (!(b_done_left && b_done_right))
    {
        if (ENCODER_Read(LEFT) < goal)
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
            b_done_left = true;
        }

        if (ENCODER_Read(RIGHT) < goal)
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
            b_done_right = true;
        }
    }

    Serial.println(ENCODER_Read(LEFT));
    Serial.println(ENCODER_Read(RIGHT));
    Serial.println("\n");

    //MOTOR_SetSpeed(LEFT,speed);
    //MOTOR_SetSpeed(RIGHT,speed);


    

    if (ENCODER_Read(LEFT) < goal)
    {
        MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX);
    }
    else
    {
        MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
        //b_done_left = true;
    }
}



/** Function to convert centimeter to number of pulse
*/
int32_t cm2pulse(float cm)
{
    float in = 0.3937 * cm;
    float nb_tour = in / (3 * PI);
    return nb_tour * 3200;
}
