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
void goForward(int distance){
  
  if(distance > 0){
    MOTOR_SetSpeed(LEFT,0.5);
    MOTOR_SetSpeed(RIGHT,0.5);
    Serial.println(ENCODER_Read(0));
    Serial.println(ENCODER_Read(1));
  }
  else{
    MOTOR_SetSpeed(LEFT,0);
    MOTOR_SetSpeed(RIGHT,0);
    Serial.println("Stop");
  }

}


/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  Serial.begin(9600);
  BoardInit();
}


int D = 10000;
int count = 0;
void loop() {
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  if(count < 60){
    goForward(D);
    D -= 5;
    count++;
  }
  //Serial.println("WWWWWWWWW");
  delay(100);// Delais pour décharger le CPU
}