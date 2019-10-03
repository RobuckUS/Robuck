#include <LibRobus.h>

#include "motor.h"

#define DIR_FORWARD 0

#if 0
#define DIR_LEFT //TODO
#endif

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_DEBUG 0.1
#define MOTOR_SPEED_MAX MOTOR_SPEED_DEBUG

#define WHEELS_DISTANCE_GUY43 18.5

/*#ifdef __GUY43__
#define WHEELS_DISTANCE_GUY43 18.5
#endif*/

int32_t cm2pulse(float cm);
int32_t angl2pulse(float angle);

/** Control two DC motors to go forward
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
    Serial.println("Enter motor_walk loop");
    while (!(b_done_left && b_done_right))
    {
        Serial.print(goal);
        Serial.print("\t");
        Serial.println(ENCODER_Read(LEFT));
        //Left motor
        if ((ENCODER_Read(LEFT) < goal) && (0 < goal))
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX);
        }
        else if ((ENCODER_Read(LEFT) > goal) && (0 > goal))
        {
            MOTOR_SetSpeed(LEFT, -MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
            Serial.println("LEFT goal accessed");
            b_done_left = true;
        }

        //Right motor
        if ((ENCODER_Read(RIGHT) < goal) && (0 < goal))
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX);
        }
        else if ((ENCODER_Read(RIGHT) > goal) && (0 > goal))
        {
            MOTOR_SetSpeed(RIGHT, -MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
            Serial.println("RIGHT goal accessed");
            b_done_right = true;
        }
    }
    Serial.println("Exit motor_walk loop");
    MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
    MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);

    /*Serial.println(ENCODER_Read(LEFT));
    Serial.println(ENCODER_Read(RIGHT));
    Serial.println("\n");*/

    //MOTOR_SetSpeed(LEFT,speed);
    //MOTOR_SetSpeed(RIGHT,speed);
}

/** Control two DC motors to turn
 * 
 * @param angle, reprensents the angle of the robot relative to it direction.
 * floating value in degree (left is negative, right is positive)
*/
void motor_turn(float angle)
{
    Serial.println("Enter motor_turn init");
    //init motor_turn
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int32_t goal = angl2pulse(angle);

    bool b_done_left = false;
    bool b_done_right = false;

    Serial.println(angle);

    //loop motor_turn
    Serial.println("Enter motor_turn loop");
    while (!(b_done_left && b_done_right))
    {
        //Left motor
        if (ENCODER_Read(LEFT) < goal)
        {
            Serial.println("+  ");
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX);
        }
        else if (ENCODER_Read(LEFT) > goal)
        {
            MOTOR_SetSpeed(LEFT, -MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
            b_done_left = true;
        }

        //Right motor
        if (ENCODER_Read(RIGHT) < (-goal))
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX);
        }
        else if (ENCODER_Read(RIGHT) > (-goal))
        {
            MOTOR_SetSpeed(RIGHT, -MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
            b_done_right = true;
        }
    }
    Serial.println("Exit motor_turn loop");
    MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
    MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
}

/** Convert centimeter to number of pulse
*/
int32_t cm2pulse(float cm)
{
    float nb_tour = (0.3937 * cm) / (3 * PI);
    return nb_tour * 3200;
}

/** Convert angle (degree) to number of pulse
 * 
*/
int32_t angl2pulse(float angle)
{
    //float nb_tour = 3.5645654353453;
    float distance = ((angle / 2) * (2 * PI * WHEELS_DISTANCE_GUY43)) / 360;
    float nb_pulse = cm2pulse(distance);
    Serial.println(distance);
    return nb_pulse;
}
