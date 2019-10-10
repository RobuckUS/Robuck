#include <LibRobus.h>
#include "motor.h"

#define JEAN 31
#define GUY 43

#define __ROBOT__ GUY

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_MAX 0.35
#define MOTOR_SPEED_TURN 0.25

int32_t cm2pulse(float cm);
int32_t angl2pulse(float angle);

#if (__ROBOT__ == JEAN)
const float wheels_diameter = 3;
const float wheels_distance = 18.45;
const float g_kp = 7E-4;
const float g_ki = 4E-7;
const float g_kd = 0;
#elif (__ROBOT__ == GUY)
const float wheels_diameter = 3;
const float wheels_distance = 18.45;
const float g_kp = 7E-4;
const float g_ki = 4E-7;
const float g_kd = 0;
#else
#error "Please specify a valid target robot (__ROBOT__)"
#endif

// Communication setup
const long serialPing = 500;
unsigned long now = 0;
unsigned long lastMessage = 0;

int32_t g_setPoint = 0;

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
    float speed_correction = 0;
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

        speed_correction = computePID(delta);

        now = millis();
        if (now - lastMessage > serialPing)
        {
#if 0
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
#endif
            lastMessage = now;
        }

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
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_MAX + speed_correction);
        }
        else if ((ENCODER_Read(RIGHT) > goal) && (0 > goal))
        {
            MOTOR_SetSpeed(RIGHT, -(MOTOR_SPEED_MAX + speed_correction));
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
    delay(300);
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
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_TURN);
        }
        else if (ENCODER_Read(LEFT) > goal)
        {
            MOTOR_SetSpeed(LEFT, -MOTOR_SPEED_TURN);
        }
        else
        {
            MOTOR_SetSpeed(LEFT, MOTOR_SPEED_STOP);
            b_done_left = true;
        }

        //Right motor
        if (ENCODER_Read(RIGHT) < (-goal))
        {
            MOTOR_SetSpeed(RIGHT, MOTOR_SPEED_TURN);
        }
        else if (ENCODER_Read(RIGHT) > (-goal))
        {
            MOTOR_SetSpeed(RIGHT, -MOTOR_SPEED_TURN);
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
    delay(300);
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
    float nb_tour = (0.3937 * cm) / (wheels_diameter * PI);
    return nb_tour * 3200;
}

/** Convert angle (degree) to number of pulse
*/
int32_t angl2pulse(float angle)
{
    //float nb_tour = 3.5645654353453;
    float distance = ((angle / 2) * (2 * PI * wheels_distance)) / 360;
    float nb_pulse = cm2pulse(distance);
    Serial.println(distance);
    return nb_pulse;
}
