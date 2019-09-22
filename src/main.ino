#include <LibRobus.h> 



/*début PID*/
unsigned long lastCheck;
double Input /*Encoder, transformer en vitesse*/, Output /*Force du moteur (+ ou -)*/, SetPoint /*vitesse*/;
double ITerm, lastInput;
double kp, ki, kd;
double outMin, outMax; /*comme les moteurs marchent entre 0 et 1, il faut regarder si le ouput est correcte*/

int SampleTime = 10; /*Fréquence de l'ajustement de l'erreur du PIB, chaque 1/100 secondes pour le moment*/
void computePID(){
  /*Temps depuis le dernier check*/
  unsigned long timeNow = millis();
  double timeElapsed = (double) (timeNow-lastCheck);
  /*Regarde si le temps est trop petit*/
  if(timeElapsed >= SampleTime){
    /*Calculer l'erreur si il y en a une sinon retourne 0 donc pas de changements*/
    double error = SetPoint - Input;
    ITerm += (ki * error) ;

    /*évite le debugging, donc le ITerm ne peut pas aller au dessus ou en dessous des valeurs max du moteur*/
    if(ITerm > outMax) ITerm = outMax;
    else if (ITerm < outMin) ITerm = outMin;
    
    double dInput = (error - lastInput);

    /*calculer la valeur de sortie*/
    Output = kp * error + ki * ITerm + kd * dInput;
    if(Output > outMax) Output=outMax;
    else if(Output < outMin) Output = outMin;


    /*enregistrer les variables*/
    lastCheck=timeNow;
    dInput = Input;
  }
}

void setTunings(double Kp, double Ki, double Kd){
  double SampleTimeInSec = ((double)SampleTime)/1000;
  kp=Kp;

  /*ajustement de ki et kd pour les rendres plus efficaces*/
  ki = Ki * SampleTimeInSec;
  kd= Kd / SampleTimeInSec;
}

/*metode pour changer la fréquence des vérifications*/
void SetSampleTime(int NewSampleTime){
  if(NewSampleTime > 0){  //Pas nécessaire comme on devrait pas configurer un temps de 0 ou plus petit, mais ça évite du debugging

  /*Si la fréquence change, il faut reajuster ki et kd pour le ratio.*/
    double ratio = (double)NewSampleTime / (double) SampleTime;
    ki *= ratio;
    kd /= ratio;
    SampleTime = (unsigned long)NewSampleTime;
  }
}

/*Methode pour configurer le minimum et maximum voltage du moteur*/
void SetOutputLimits(double Min, double Max){
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;
    
   if(Output > outMax) Output = outMax;
   else if(Output < outMin) Output = outMin;
 
   if(ITerm> outMax) ITerm= outMax;
   else if(ITerm< outMin) ITerm= outMin;
}

/*Fin du PID*/




/*Début code robot*/
int pulsesLeft;
int pulsesRight;
double circumference = PI * pow((7.62/2),2); //7.62 est 3 pouces en centimetre
long timeBeggining;
long timeNow;

void setup(){
  outMin = -1.0;
  outMax = 1.0;
  timeBeggining= millis();
  
  BoardInit();
  
}

double distance(int motor) { /*distance par roue*/
  int pulses;
  if(motor =0){
    pulses= pulsesLeft;
  }
  else if(motor = 1){
    pulses = pulsesRight;
  }
  
  return (pulses /3600) * circumference;
}

double speed(int motor){
  return (timeNow-timeBeggining)/distance(motor);
}

void loop() {
  pulsesLeft = ENCODER_Read(0);
  pulsesRight = ENCODER_Read (1);
  SetPoint = 10;
  timeNow= millis();
  Input= speed(0);
  computePID();
  MOTOR_SetSpeed(0, Output);
  timeNow= millis();
  Input= speed(1);
  computePID();
  MOTOR_SetSpeed(1, Output);
  
  delay(10);
}
 