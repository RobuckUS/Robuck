/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <Arduino.h>
#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <sens.h>
#include <combat.h>
#include <SharpIR.h>
#include <motor.h>

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */

#define JEAN 31
#define GUY 43

#define DELAY false

//Choose JEAN or GUY
const int g_robot_name = JEAN;

//Choose RED, GREEN, BLUE or YELLOW
const combat_color_t targetColor1 = RED;
const combat_color_t targetColor2 = RED;

/* ****************************************************************************
Fonctions
**************************************************************************** */

/* ****************************************************************************
Fonctions d'initialisation
**************************************************************************** */

void setup()
{
    BoardInit();
    sens_init();
    Serial.begin(9600);
    Serial.println("\n\n---RESET---\n");
}

/* ****************************************************************************
Fonctions de boucle infini
**************************************************************************** */

void loop()
{
    // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels

    while (!ROBUS_IsBumper(REAR))
        ; //Wait for rear bumper press

    switch (g_robot_name)
    {
    case JEAN:
        combat_robot1(targetColor1);
        break;

    case GUY:
#if DELAY
        delay(60000);
#endif
        combat_robot2(targetColor2);
        break;

    default:
        Serial.println("The should be a name to the robot. Please set g_robot_name");
        while (1)
            ; // halt!
        break;
    }
}
