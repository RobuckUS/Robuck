#include "combat.h"
#include "sens.h"
#include <motor.h>
#include <SharpIR.h>
#include <LibRobus.h>


#define lineFollowSensor0 22
#define lineFollowSensor1 24
#define lineFollowSensor2 37

void combat_robot1(combat_color_t ColorToGo)
{ 
    //ServoMoteur
    SERVO_Enable(0);
    SERVO_SetAngle(0,1);
    switch (ColorToGo)
    {
    case RED:
     
        break;
    case GREEN:

        break;
    case BLUE:
        motor_turn(90);
        motor_walk(5);
        Serial.println(digitalRead(lineFollowSensor1));
                Serial.println(digitalRead(lineFollowSensor1));

        while(digitalRead(lineFollowSensor1)==WHITE_NOT_LINE )
        {
             Serial.println(digitalRead(lineFollowSensor1));

            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
            
        }
        
        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(1);
        motor_turn(38);
        motor_walk(3);
        while(1){
            sens_followLineIR();
            if(digitalRead(lineFollowSensor1)==BLACK_LINE &&digitalRead(lineFollowSensor0)==BLACK_LINE && digitalRead(lineFollowSensor1)==BLACK_LINE)
                {
                    motor_walk(6);
                    SERVO_SetAngle(0,90);
                    break;
                }
            }

        
        motor_quickStop();
        delay(200);
        motor_quickWalk();
        delay(500);
        motor_quickStop();
        delay(200);
        motor_turn(180);
        while(digitalRead(lineFollowSensor1)==BLACK_LINE &&digitalRead(lineFollowSensor0)==BLACK_LINE && digitalRead(lineFollowSensor1)==BLACK_LINE)
        {
            sens_followLineIR();
        }
        SERVO_SetAngle(0, 1);
        break;
    case YELLOW:
        motor_turn(-90);
        motor_walk(5);
        Serial.println(digitalRead(lineFollowSensor1));
                Serial.println(digitalRead(lineFollowSensor1));

        while(digitalRead(lineFollowSensor1)==WHITE_NOT_LINE )
        {
         Serial.println(digitalRead(lineFollowSensor1));

            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
            
        }
        
        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(1);
        motor_turn(-38);

        while(sens_getColor()!=0x02|| sens_getColor()!=BLUE || sens_getColor()!=RED || sens_getColor()!=GREEN)
        {
            sens_followLineIR();
            if(sens_getColor()!=0x02)
            {
                break;
            }
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(8);
        SERVO_SetAngle(0,0);
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