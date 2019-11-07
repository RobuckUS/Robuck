#include "combat.h"
#include "sens.h"
#include <motor.h>
#include <SharpIR.h>
#include <LibRobus.h>

#define angleServo 110
#define lineFollowSensor0 22
#define lineFollowSensor1 24
#define lineFollowSensor2 37

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
                break;
            }
        }

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(4000);

        motor_turn(90);
        motor_walk(100);
        motor_quickStop();
        SERVO_SetAngle(0, 1);
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
            if (digitalRead(lineFollowSensor1) == BLACK_LINE && digitalRead(lineFollowSensor0) == BLACK_LINE && digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                SERVO_SetAngle(0, 0);
                MOTOR_SetSpeed(LEFT, -0.0);
                MOTOR_SetSpeed(RIGHT, -0.0);
                break;
            }
        }
        delay(2000);

        MOTOR_SetSpeed(LEFT, -0.2);
        MOTOR_SetSpeed(RIGHT, -0.2);
        delay(4000);

        motor_quickStop();
        SERVO_SetAngle(0, 1);
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
        MOTOR_SetSpeed(1, -0.3);
        MOTOR_SetSpeed(0, -0.3);
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

        while (digitalRead(lineFollowSensor1) != BLACK_LINE &&
               digitalRead(lineFollowSensor0) != BLACK_LINE &&
               digitalRead(lineFollowSensor1) != BLACK_LINE)
        {
            sens_followLineIR();
        }
        motor_walk(32);

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor1) == BLACK_LINE)
            {
                motor_quickStop();
                break;
            }
        }
        break;

    case BLUE:
        MOTOR_SetSpeed(1, -0.3);
        MOTOR_SetSpeed(0, -0.3);
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

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor2) == BLACK_LINE)
            {
                motor_quickStop();
                break;
            }
        }

        while (1)
        {
            MOTOR_SetSpeed(0, 1);
            MOTOR_SetSpeed(1, 1);
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor2) == BLACK_LINE)
            {
                motor_quickStop();
                break;
            }
        }
        break;

    case YELLOW:
        MOTOR_SetSpeed(1, -0.3);
        MOTOR_SetSpeed(0, -0.3);
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

        while (1)
        {
            sens_followLineIR();
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor2) == BLACK_LINE)
            {
                motor_quickStop();
                break;
            }
        }

        motor_walk(32);

        while (1)
        {
            MOTOR_SetSpeed(0, 1);
            MOTOR_SetSpeed(1, 1);
            if (digitalRead(lineFollowSensor1) == BLACK_LINE &&
                digitalRead(lineFollowSensor0) == BLACK_LINE &&
                digitalRead(lineFollowSensor2) == BLACK_LINE)
            {
                motor_quickStop();
                break;
            }
        }
        break;

    default:
        break;
    }
}
