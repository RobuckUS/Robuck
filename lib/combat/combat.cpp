#include "combat.h"
#include "sens.h"
#include <motor.h>
#include <SharpIR.h>
#include <LibRobus.h>

#define angleServo 115
#define lineFollowSensor0 22
#define lineFollowSensor1 24
#define lineFollowSensor2 37

void follow_line_until_all_black_line_THEN_stop();
void race_for_5_a_8_DASF_Unreal();

void combat_robot1(combat_color_t ColorToGo)
{
    //ServoMoteur
    SERVO_Enable(0);
    SERVO_SetAngle(0, 1);
    switch (ColorToGo)
    {
    case RED:
        motor_turn(-90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }
        motor_quickStop();
        delay(200);

        motor_turn(90);
        motor_walk(55);
        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }
        motor_walk(3);
        motor_turn(-40);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                motor_turn(-5);
                motor_walk(7);
                SERVO_SetAngle(0, angleServo);
                break;
            }
        }
        delay(2000);

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(2000);

        MOTOR_SetSpeed(LEFT, 0);
        MOTOR_SetSpeed(RIGHT, 0);
        motor_turn(195);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                SERVO_SetAngle(0, 0);
                MOTOR_SetSpeed(LEFT, -0.0);
                MOTOR_SetSpeed(RIGHT, -0.0);
                break;
            }
        }

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(4000);

        motor_quickStop();
        SERVO_SetAngle(0, 1);
        break;

    case GREEN:
        motor_turn(90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }
        motor_quickStop();
        delay(200);

        motor_turn(-90);
        motor_walk(55);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }
        motor_walk(3);
        motor_turn(40);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                motor_turn(-5);
                motor_walk(7);
                SERVO_SetAngle(0, angleServo);
                break;
            }
        }
        delay(2000);

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(2000);

        MOTOR_SetSpeed(LEFT, 0);
        MOTOR_SetSpeed(RIGHT, 0);
        motor_turn(195);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                SERVO_SetAngle(0, 0);
                MOTOR_SetSpeed(LEFT, -0.0);
                MOTOR_SetSpeed(RIGHT, -0.0);
                delay(1000);
                break;
            }
        }
        break;

    case BLUE:
        motor_turn(90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(1);
        motor_turn(38);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                motor_turn(-5);
                motor_walk(7);
                SERVO_SetAngle(0, angleServo);
                break;
            }
        }
        delay(2000);

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(2000);

        MOTOR_SetSpeed(LEFT, 0);
        MOTOR_SetSpeed(RIGHT, 0);
        motor_turn(195);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor2) == BLACK_LINE)
            {
                SERVO_SetAngle(0, 0);
                MOTOR_SetSpeed(LEFT, 0.0);
                MOTOR_SetSpeed(RIGHT, 0.0);
                delay(1000);
                break;
            }
        }
        break;

    case YELLOW:
        motor_turn(-90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(1);
        motor_turn(-38);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                motor_turn(5);
                motor_walk(7);
                SERVO_SetAngle(0, angleServo);
                break;
            }
        }
        delay(2000);

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(2000);

        MOTOR_SetSpeed(LEFT, 0);
        MOTOR_SetSpeed(RIGHT, 0);
        motor_turn(190);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                SERVO_SetAngle(0, 0);
                motor_quickStop();
                delay(1000);
                break;
            }
        }
        
        break;

    default:
        break;
    }
    MOTOR_SetSpeed(LEFT, -0.2);
    MOTOR_SetSpeed(RIGHT, -0.2);
    delay(6000);
    motor_quickStop();
}

void combat_robot2(combat_color_t ColorToGo)
{
    switch (ColorToGo)
    {
    case RED:
        MOTOR_SetSpeed(LEFT, -0.3);
        MOTOR_SetSpeed(RIGHT, -0.3);
        delay(900);

        motor_quickStop();
        motor_turn(-90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_turn(88);
        motor_walk(80);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }
        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(7);
        delay(200);

        motor_turn(135);

        follow_line_until_all_black_line_THEN_stop();
        break;

    case GREEN:
        MOTOR_SetSpeed(LEFT, -0.3);
        MOTOR_SetSpeed(RIGHT, -0.3);
        delay(900);

        motor_quickStop();
        motor_turn(90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_turn(-88);
        motor_walk(80);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }
        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(7);
        delay(200);

        motor_turn(-135);

        follow_line_until_all_black_line_THEN_stop();
        break;

    case BLUE:
        MOTOR_SetSpeed(LEFT, -0.3);
        MOTOR_SetSpeed(RIGHT, -0.3);
        delay(1000);

        motor_quickStop();
        motor_turn(90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(7);
        motor_turn(-135);
        delay(200);

        follow_line_until_all_black_line_THEN_stop();
        break;

    case YELLOW:
        MOTOR_SetSpeed(LEFT, -0.3);
        MOTOR_SetSpeed(RIGHT, -0.3);
        delay(1000);

        motor_quickStop();
        motor_turn(-90);
        motor_walk(10);

        while (digitalRead(lineFollowSensor1) == WHITE_NOT_LINE)
        {
            MOTOR_SetSpeed(LEFT, 0.4);
            MOTOR_SetSpeed(RIGHT, 0.4);
        }

        MOTOR_SetSpeed(LEFT, 0.0);
        MOTOR_SetSpeed(RIGHT, 0.0);
        motor_walk(7);
        delay(200);

        motor_turn(135);
        delay(200);

        follow_line_until_all_black_line_THEN_stop();
        break;

    default:
        break;
    }

    race_for_5_a_8_DASF_Unreal();
}

void follow_line_until_all_black_line_THEN_stop()
{
    while (!(digitalRead(lineFollowSensor0) == BLACK_LINE &&
             digitalRead(lineFollowSensor1) == BLACK_LINE &&
             digitalRead(lineFollowSensor2) == BLACK_LINE))
    {
        sens_followLineIR();
    }
    motor_quickStop();
}

void race_for_5_a_8_DASF_Unreal()
{
    MOTOR_SetSpeed(LEFT, 0.7);
    MOTOR_SetSpeed(RIGHT, 0.7);
    delay(2500);

    motor_quickStop();
}
