#include "combat.h"
#include <sens.h>
#include <motor.h>
#include <SharpIR.h>
#include <LibRobus.h>


void combat_robot1(combat_color_t ColorToGo)
{
    /*motor_turn(180);

    motor_walk(40); // avance tant que trouve ligne noir

    motor_turn(-90);

    //sens_followLineIR();
    motor_walk(50);

    if(sens_getColor() == ColorToGo)
    {
        
    }else if(sens_getColor() == BLUE)
    {
        if(ColorToGo == RED)
        {
            delay(30);
            motor_turn(-135);
            delay(30);
            //motor_walk(5);
            //sens_followLineIR();
            motor_walk(100);
            delay(30);
            //Put get the ball
            motor_turn(180);
            delay(30);
            motor_walk(50);
            delay(30);
            //Put Drop the ball

            // go away
            // do a move back function

        }else if(ColorToGo == GREEN)
        {
            delay(30);
            motor_turn(-90);
            delay(30);
            motor_walk(100);
            delay(30);
            //Put get the ball
            motor_turn(180);
            delay(30);
            motor_walk(50);
            delay(30);
            //Put Drop the ball
            
            //go away
            // do a move back function

        }else if(ColorToGo == YELLOW)
        {
            delay(30);
            motor_turn(180);
            delay(30);
            motor_walk(100);
            delay(30);
            //Put get the ball

            motor_turn(180);
            delay(30);
            motor_walk(50);

            //Put Drop the ball

            //Go Away probably need a move back function

        }

    }else if(sens_getColor() == YELLOW)
    {

    }*/

    delay(300);
    motor_walk(39);
    if(ColorToGo == BLUE)
    {
        motor_turn(135);
        delay(300);
        motor_walk(15);
        delay(200);
        /*for(int i = 0; i < 20; i++){
            Serial.println(i);
            sens_followLineIR();
        }
        sens_followLineIR();*/
        motor_walk(100);
        bool motorOFF = false;
        while(motorOFF == false){
            MOTOR_SetSpeed(LEFT,0);
            MOTOR_SetSpeed(RIGHT,0);
        }
        /*while(sens_getColor() != ColorToGo)
        {
            sens_followLineIR();
        }*/
        /*if(sens_getColor() == ColorToGo){
            MOTOR_SetSpeed(LEFT,0);
            MOTOR_SetSpeed(RIGHT,0);
            delay(300);
            motor_turn(180);
            delay(200);
            motor_walk(5);
            sens_followLineIR();
            
        }
        else
        {
            Serial.print("error");
            MOTOR_SetSpeed(LEFT,0);
            MOTOR_SetSpeed(RIGHT,0);
        }*/
        
        
        
    }
    else if(ColorToGo == GREEN)
    {
        motor_turn(45);

    }
    else if(ColorToGo == YELLOW)
    {
        motor_turn(-130);
    }
    else if(ColorToGo == RED)
    {
        motor_turn(-45);
    }
    /*delay(300);
    sens_followLineIR();*/

}
SharpIR mySensor = SharpIR(0,1080);
int distance_cm;
void combat_robot2()
{
    //sens_followLineIR();
    int angleFindBall = 0;
    Serial.println(distance_cm);

    while (mySensor.distance() > 40){
        angleFindBall += 5;
        if(angleFindBall >= 0 && angleFindBall >= 90){
            angleFindBall += 5;
        }else
        {
            angleFindBall -= 5;
        }
        motor_turn(angleFindBall);
    }
    motor_walk(mySensor.distance -2);
    
    //distance_cm = mySensor.distance();
    Serial.println(distance_cm);
    delay(400);
    //code for robot 2 here
}
