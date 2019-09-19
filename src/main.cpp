/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <Arduino.h>
#include <LibRobus.h> // Essentielle pour utiliser RobUS



/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void maFonction(){
  // code
}


/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
  int32_t main_tmp_speed_test[32] = {
    0,

    0.25,
    0.5,
    0.75,
    1,
    0,

    -0.25,
    -0.5,
    -0.75,
    -1,
    0,

    0.25,
    -0.25,
    0.5,
    -0.5,
    0.75,
    -0.75,
    1,
    -1,
    0,

    1,
    0,
    
    -1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  };

  for (size_t i = 0; i < 32; i++)
  {
    MOTOR_SetSpeed(LEFT,main_tmp_speed_test[i]);
    MOTOR_SetSpeed(RIGHT,main_tmp_speed_test[i]);
    delay(1000);
  }

}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}
