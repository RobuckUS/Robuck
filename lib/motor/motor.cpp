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
        else if(ENCODER_Read(LEFT) > goal)
        {
            MOTOR_SetSpeed(LEFT, -MOTOR_SPEED_MAX);
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
        else if(ENCODER_Read(RIGHT) > goal)
        {
            MOTOR_SetSpeed(RIGHT,-MOTOR_SPEED_MAX);
        }
        else
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
            b_done_right = true;
        }
        
    }

    /*Serial.println(ENCODER_Read(LEFT));
    Serial.println(ENCODER_Read(RIGHT));
    Serial.println("\n");*/

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
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    int32_t goal = angl2pulse(angle);

    bool b_done_left = false;
    bool b_done_right = false;

    Serial.println(angle);

    //TODO --> rentre pas dans le else quand on rentre une angle négative dans le cpp
    if(angle > 0)
    {
        while (!(b_done_right))
        {
            if(ENCODER_Read(RIGHT) < goal)
            {
                Serial.println("Gauche!!");
                MOTOR_SetSpeed(RIGHT,MOTOR_SPEED_MAX);
                MOTOR_SetSpeed(LEFT,-MOTOR_SPEED_MAX);
            }
            else
            {
                MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_STOP);
                b_done_right = true;
            }
        }
        
        
    }
    else
    {
        while (!(b_done_left))
        {
            if(ENCODER_Read(LEFT) < goal){

                Serial.println("Droite!!");
                MOTOR_SetSpeed(LEFT,MOTOR_SPEED_MAX);
                MOTOR_SetSpeed(RIGHT,-MOTOR_SPEED_MAX);
            }
            else
            {
                MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
                b_done_left = true;
            }
        }
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

/** Function to convert angle to number of pulse
*/
int32_t angl2pulse(float angle)
{
    //float nb_tour = 3.5645654353453;
    float distance = ((angle/2) * (2 * PI * WHEELS_DISTANCE_GUY43)) / 360;
    float nb_pulse = cm2pulse(distance);
    Serial.println(distance);
    return nb_pulse;

}