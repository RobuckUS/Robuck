#include <LibRobus.h> 

#define MOTOR_SPEED_STOP 0
#define MOTOR_SPEED_DEBUG 0.1
#define MOTOR_SPEED_MAX MOTOR_SPEED_DEBUG

/*début PID*/

double kp=2E-4, ki=3.2E-3;
const double outMin = -1.0;
const  double outMax = 1.0; /*comme les moteurs marchent entre 0 et 1, il faut regarder si le ouput est correcte*/
double Output;
void computePID()
{
  unsigned long lastTime;
  double derrivative;
  unsigned long now = millis();
  int timeChange = (now - lastTime);
  double error=ENCODER_Read(0)-ENCODER_Read(1);
  derrivative = error/timeChange;
  Output=kp*derrivative + ki * error ;
  if(Output> outMax){
    Output=outMax;
  }
  lastTime=now;
}
void turn90left(){
  while(ENCODER_Read(1)<=cm2pulse(14.92*2)){
    MOTOR_SetSpeed(1, 0.3);
    delay(10);
  }
  
  MOTOR_SetSpeed(1, 0.0);
  MOTOR_SetSpeed(0, 0.0);
  ENCODER_Reset(0);
  ENCODER_Reset(1);
}
void turn90right(){
  while(ENCODER_Read(0)<=cm2pulse(14.92*2 )){
    MOTOR_SetSpeed(0, 0.3);
    delay(10);
  }
  MOTOR_SetSpeed(0, 0.0);
  MOTOR_SetSpeed(1, 0.0);
  ENCODER_Reset(1);
}
void turn45right(){
  while(ENCODER_Read(0)<=cm2pulse(14.92)){
    MOTOR_SetSpeed(0, 0.3);
    delay(10);
  }
  MOTOR_SetSpeed(0, 0.0);
  ENCODER_Reset(0);
}
void turn45left(){
  while(ENCODER_Read(1)<=cm2pulse(14.92)){
    MOTOR_SetSpeed(1, 0.3);
    delay(10);
  }
  MOTOR_SetSpeed(1, 0.0);
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
      MOTOR_SetSpeed(0, 0.3);
      computePID();
      MOTOR_SetSpeed(1, Output);
      delay(10);
    }
  }
  else{
    while(ENCODER_Read(0) >= cm2pulse(cm)){
      MOTOR_SetSpeed(0, -0.3);
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
  avanceCM(50);
  delay(2000);
  turn90left();
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  delay(2000);
  turn90right();
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  delay(2000);
  turn45right();
  ENCODER_Reset(0);
  ENCODER_Reset(1);    
  delay(2000);
  turn45left();
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  delay(10000); 
  avanceCM(-122.5);
  MOTOR_SetSpeed(0, 0.0);
  MOTOR_SetSpeed(1, 0.0);
  delay(20000);
} 