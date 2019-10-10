#include <Arduino.h>
#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <motor.h>

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */

/* ****************************************************************************
Fonctions
**************************************************************************** */

void waitBumper()
{
  while (!ROBUS_IsBumper(REAR))
  {
  }

  AX_BuzzerON();
  delay(100);
  AX_BuzzerOFF();
}

void pathDemo1()
{
  const int timeout = 2000;
  motor_walk(10);
  delay(timeout);
  motor_turn(90);
  delay(timeout);
  motor_walk(-10);
  delay(timeout);
  motor_turn(-90);
  delay(timeout);
}

void pathDemo2()
{
  const int timeout = 2000;
  motor_walk(200);
  delay(timeout);
  motor_turn(360);
  delay(timeout);
}

void pathRedSquare1()
{
  motor_walk(76);
  motor_turn(90);

  motor_walk(89);
  motor_turn(-90);

  motor_walk(89);
  motor_turn(-90 - 45);

  motor_walk(231);
  motor_turn(-90 - 45);

  motor_walk(84);
  motor_turn(-90);
}

void path2m()
{
  motor_walk(200);
}

void pathTour(int tour)
{
  motor_turn(tour * 360);
}

void pathPrep1()
{
  const int timeout = 3000;
  motor_walk(100 + 45 / 2);
  motor_turn(-90);

  motor_walk(90);
  motor_turn(90);

  motor_walk(65 + 45 / 2 + 19 / 2);
  motor_turn(45);

  motor_walk(172 - 19 / 2 + 45 / 2);
  motor_turn(-90);

  motor_walk(71 - 45 / 2 + 18 / 2);
  motor_turn(45);

  motor_walk(18 / 2 + 100);

  delay(timeout);
  motor_walk(45);
  delay(timeout);
  motor_turn(180);
  motor_walk(45);
  motor_walk(500);
  motor_turn(180);
}

void pathEmpty()
{
  motor_walk(0);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);
}

void pathTurnAround()
{
  motor_walk(45);  //Go out of the box
  motor_turn(180); //Turn around
  motor_walk(45);  //Go back near the box
}

void pathReal()
{
  motor_walk(100 + 45 / 2);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(100 + 45 / 2);
}

void pathRealRewind()
{
  motor_walk(100 + 45 / 2);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(0);
  motor_turn(0);

  motor_walk(100 + 45 / 2);
}

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */

void setup()
{
  BoardInit();
  Serial.begin(9600);
  Serial.println("\n---BEGIN---");
}

/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */

void loop()
{
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels

  waitBumper();

  delay(500);
  pathReal();
  waitBumper();
  pathTurnAround();

  waitBumper();
  pathRealRewind();
  waitBumper();
  pathTurnAround();
}
