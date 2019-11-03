#include "combat.h"
#include <sens.h>
#include <motor.h>
#include <SharpIR.h>
#include <LibRobus.h>


void combat_robot1(combat_color_t ColorToGo)
{
    //ServoMoteur
    //SERVO_Enable(0);
    //SERVO_SetAngle(0,0);
    switch (ColorToGo)
    {
    case RED:
     
        break;
    case GREEN:

        break;
    case BLUE:

        break;
    case YELLOW:

        break;
    default:
        break;
    }

    
}

void combat_robot2(combat_color_t ColorToGo)
{
    switch (ColorToGo)
    {
    case RED:
        motor_turn(-90);
        motor_walk(40);
        motor_turn(90);
        motor_walk(75);
        motor_turn(135);        
        break;
    case GREEN:
        motor_turn(90);
        motor_walk(40);
        motor_turn(-90);
        motor_walk(75);
        motor_turn(-135);
        break;
    case BLUE:
        motor_turn(90);
        motor_walk(40);
        motor_turn(-135);
        break;
    case YELLOW:
        motor_turn(-90);
        motor_walk(40);
        motor_turn(135);
        break;
    default:
        break;
    }

    while(/*sens_getColor() ==  ColorToGo*/!ROBUS_IsBumper(FRONT))
    {
        sens_followLineIR();

    }
    motor_walk(5);
}

/*SharpIR mySensor = SharpIR(4,1080);
int distance_cm;*/
    //int angleFindBall = 0;
    /*while (mySensor.distance() > 40){
        angleFindBall += 5;
        if(angleFindBall >= 0 && angleFindBall >= 90){
            angleFindBall += 5;
        }else
        {
            angleFindBall -= 5;
        }
        motor_turn(angleFindBall);
    }
    motor_walk(mySensor.distance -2);*/