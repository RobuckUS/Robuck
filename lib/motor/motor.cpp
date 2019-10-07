#include <LibRobus.h>

#include "motor.h"

#define DIR_FORWARD 0

#if 0
#define DIR_LEFT //TODO
#endif

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_DEBUG 0.2
#define MOTOR_SPEED_MAX MOTOR_SPEED_DEBUG

#define WHEELS_DISTANCE_GUY43 18.5

/*#ifdef __GUY43__
#define WHEELS_DISTANCE_GUY43 18.5
#endif*/

int32_t cm2pulse(float cm);
int32_t angl2pulse(float angle);

//PID constants
float g_kp = 5E-4;
float g_ki = 1E-7;
float g_kd = 0;

int32_t g_setPoint;

float computePID(int32_t input);

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
    float speed_out = 0;
    int32_t enc_l = 0;
    int32_t enc_r = 0;
    int32_t delta = 0;

    bool b_done_left = false;
    bool b_done_right = false;

    g_setPoint = 0;

    //loop motor_walk
    Serial.println("Enter motor_walk loop");
    MOTOR_SetSpeed(LEFT, MOTOR_SPEED_MAX);
    MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX);
    while (!(b_done_left && b_done_right))
    {
        enc_l = ENCODER_Read(LEFT);
        enc_r = ENCODER_Read(RIGHT);
        delta = enc_r - enc_l;

        speed_out = computePID(delta);
        delay(100);
        /*
        Serial.print("Goal: ");
        Serial.print(goal);
        Serial.print("\t");

        Serial.print("Enc_L: ");
        Serial.print(enc_l);
        Serial.print("\t");

        Serial.print("Enc_R: ");
        Serial.print(enc_r);
        Serial.print("\t");

        Serial.print("Delta: ");
        Serial.print(delta);
        Serial.print("\t");

        Serial.print("Speed: ");
        Serial.println(speed_out);
*/
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
            MOTOR_SetSpeed(RIGHT, speed_out);
        }
        else if ((ENCODER_Read(RIGHT) > goal) && (0 > goal))
        {
            MOTOR_SetSpeed(RIGHT, -speed_out);
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

/** Compute PID
*/
float computePID(int32_t input)
{
    static unsigned long currentTime;
    static unsigned long previousTime;
    static int32_t elapsedTime;

    static int32_t error;
    static int32_t lastError;

    static int32_t cumError;
    static int32_t rateError;

    currentTime = millis();
    elapsedTime = currentTime - previousTime;

    error = g_setPoint - input;                    // determine error
    cumError += error * elapsedTime;               // compute integral
    rateError = (error - lastError) / elapsedTime; // compute derivative

    float output = (g_kp * error) + (g_ki * cumError) + (g_kd * rateError); //PID output

    lastError = error;
    previousTime = currentTime;

    return output;
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
