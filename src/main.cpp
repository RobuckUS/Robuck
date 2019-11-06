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

const int g_robot_name = GUY;

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

    //Go to War()
    switch (g_robot_name)
    {
    case JEAN:
        Serial.print("Jean POWER!!");
        if(ROBUS_IsBumper(LEFT))
        {
            combat_robot1(YELLOW );
        }
        if(ROBUS_IsBumper(RIGHT))
        {
             combat_robot1(BLUE );

        }
        if(ROBUS_IsBumper(FRONT))
        {
            combat_robot1(GREEN);
        }
        if(ROBUS_IsBumper(REAR))
        {
            combat_robot1(RED);
        }
        break;

    case GUY:
    
        if(ROBUS_IsBumper(REAR))
        {
            combat_robot2(YELLOW);
        }
        break;
        

    default:
        Serial.println("The should be a name to the robot. Please set g_robot_name");
       
        break;
    }
}

/* ****************************************************************************
Fonctions de boucle infini
**************************************************************************** */

void loop()
{
//Go to War()
    switch (g_robot_name)
    {
    case JEAN:
        Serial.print("Jean POWER!!");
        if(ROBUS_IsBumper(LEFT))
        {
            combat_robot1(YELLOW );
        }
        if(ROBUS_IsBumper(RIGHT))
        {
             combat_robot1(BLUE );

        }
        if(ROBUS_IsBumper(FRONT))
        {
            combat_robot1(GREEN);
        }
        if(ROBUS_IsBumper(REAR))
        {
            combat_robot1(RED);
        }
        break;

    case GUY:
        if(ROBUS_IsBumper(LEFT))
        {
            combat_robot2(YELLOW);
        }
        break;
        

    default:
        Serial.println("The should be a name to the robot. Please set g_robot_name");
       
        break;
    }
}
