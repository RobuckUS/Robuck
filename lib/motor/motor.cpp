#include "motor.h"

#define DIR_FORWARD 0
#define DIR_LEFT

int32_t cm2pulse(float cm)
{
    float in = 0.3937 * cm;
    float nb_tour = in / 3;
    return nb_tour * 3200;

}

/** Function to control the two DC motors on robots
 * 
 * @param distance, reprensents direction and distance of the robot.
 * floating value in centimer between [-1.0, 1.0]
*/
void motor_walk(float distance)
{
    if (ENCODER_Read(LEFT) < 3200 )
    {
        MOTOR_SetSpeed(LEFT,0.1);
    }
    else
    {
        MOTOR_SetSpeed(LEFT,0);
    }
    
    if (ENCODER_Read(RIGHT) < 3200 )
    {
        MOTOR_SetSpeed(RIGHT,0.1);
    }
    else
    {
        MOTOR_SetSpeed(RIGHT,0);
    }
    
    
    Serial.println(ENCODER_Read(LEFT));
    Serial.println(ENCODER_Read(RIGHT));
    Serial.println("\n");



    //MOTOR_SetSpeed(LEFT,speed);
    //MOTOR_SetSpeed(RIGHT,speed);
}

void motor_turn(float direction, float speed)
{
    //TODO
}
