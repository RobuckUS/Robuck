  #include <LibRobus.h> 

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_DEBUG 0.1
#define MOTOR_SPEED_MAX MOTOR_SPEED_DEBUG

/*début PID*/

double kp=2.2E-4, ki=3.2E-3;
const double outMin = -1.0;
const  double outMax = 1.0; /*comme les moteurs marchent entre 0 et 1, il faut regarder si le ouput est correcte*/
double Output;
void computePID()
{
  unsigned long lastTime=0;

  double derrivative=0;
  unsigned long now = millis();
  int timeChange = (now - lastTime);
  double error=ENCODER_Read(0)-ENCODER_Read(1);
  derrivative = error/timeChange;
  Output=kp*derrivative + ki * error ;
  if(Output> outMax){
    Output=outMax;
  }
  else if (Output<outMin){
    Output=outMin;
  }
  lastTime=now;
}
void tourne180(){
  int pulses = cm2pulse((92.5/360)*(2*18.5*PI));
  Serial.print(pulses);
  while(ENCODER_Read(1)<=pulses){
    MOTOR_SetSpeed(1, 0.27);
  }
  MOTOR_SetSpeed(1, 0.0);
  while(ENCODER_Read(0)>=(pulses*-1)){
     MOTOR_SetSpeed(0, -0.27);
  }
  MOTOR_SetSpeed(0, 0.0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}
void tournegauche(float angle){
  int pulses = cm2pulse((angle/360)*(2*18.5*PI));
  
  while(ENCODER_Read(1)<=pulses){
    MOTOR_SetSpeed(1, 0.3);
    delay(10);
  }
  MOTOR_SetSpeed(1, 0.0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}
void tournedroite(float angle){
  int pulses = cm2pulse((angle/360)*(2*18.5*PI));
  while(ENCODER_Read(0)<=pulses){
    MOTOR_SetSpeed(0, 0.3);
    delay(10);
  }
  MOTOR_SetSpeed(0, 0.0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}
int32_t cm2pulse(float cm)
{
    float in = 0.3937 * cm;
    float nb_tour = in / (3 * PI);
    return nb_tour * 3200;
}
void avanceCM(float cm){
  if(cm>0){
    while(ENCODER_Read(0)<= cm2pulse(cm)){
      MOTOR_SetSpeed(0, 0.27);
      computePID();
      MOTOR_SetSpeed(1, Output);
      delay(10);
    }
  }
  else{
    while(ENCODER_Read(0) >= cm2pulse(cm)){
      MOTOR_SetSpeed(0, -0.27);
      computePID();
      MOTOR_SetSpeed(1, Output);
      delay(10);
    }
  }
  MOTOR_SetSpeed(0, 0.0);
  MOTOR_SetSpeed(1, 0.0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}
void setup(){
  BoardInit();
  Serial.begin(9600);
}
void loop() {
  
  delay(200);
  avanceCM(107.5);
  delay(200);
  tournegauche(90);
  delay(200);
  avanceCM(80);
  delay(200);
  tournedroite(90);
  delay(200);
  avanceCM(77.5);
  delay(200);
  tournedroite(37);  
  delay(200);
  avanceCM(172.5);
  delay(200);
  tournegauche(90);
  delay(200); 
  avanceCM(54.5);
  delay(200);
  tournedroite(40);
  delay(200);
  avanceCM(100);
  MOTOR_SetSpeed(0, 0.0);
  MOTOR_SetSpeed(1, 0.0);
  delay(200);
  tourne180();
  delay(200);
  avanceCM(130);
  delay(200);
  tournegauche(48);
  delay(200);
  avanceCM(55.5);
  delay(200);
  tournedroite(90);
  delay(200);
  avanceCM(169);
  delay(200);
  tournegauche(55);  
  delay(200);
  avanceCM(77.5);
  delay(200);
  tournegauche(90);
  delay(200);
  avanceCM(75);
  delay(200);
  tournedroite(86);
  delay(200);
  avanceCM(117.5);





} 