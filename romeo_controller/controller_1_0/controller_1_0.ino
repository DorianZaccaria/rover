#include <Servo.h>
Servo servo1;                                                 // Distance sensor servo
Servo servo2;                                                 // Servo for horizontal rotation of the webcam
Servo servo3;                                                 // Servo for vertical rotation of the webcam

int pos=0;                                                    //Servos' position
int URPWM=3;                                                  //PWM pim on romeo controller
int URTRIG=13;                                                //Triger pin on romeo controller

//Standard PWM DC control
int E1 = 5;                                                   //M1 Speed Control
int E2 = 6;                                                   //M2 Speed Control
int M1 = 4;                                                   //M1 Direction Control
int M2 = 7;                                                   //M1 Direction Control

unsigned int Distance=0;                                      //Distance for the sensor
uint8_t EnPwmCmd[4]={0x44,0x22,0xbb,0x01};                    //Command for the URM37 v3.2 ultrasonic sensor


void stop(void)                                               //Stop
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
}
void advance(char a,char b)                                   //Move forward
{
  analogWrite (E1,a);                                         //PWM Speed Control
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}
void back_off (char a,char b)                                 //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}
void turn_L (char a,char b)                                   //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
}
void turn_R (char a,char b)                                   //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
}

void setup(){
  int i;

  Serial.begin(115200);
//  servo1.attach(9);
//  servo2.attach(10);
//  servo3.attach(11);

  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);

//  servo3.write(100);

//  PWM_Mode_Setup();
}

void loop(){
//  PWM_Mode();
//  if (Distance < 10)
//    stop();

  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
      case 'w':                                               //Move Forward
//        servo1.write(90);
//        servo2.write(90);
//        delay(5);
        advance (255,255);                                    //move forward in max speed
        break;
      case 's':                                               //Move Backward
        back_off (255,255);                                   //move back in max speed
        break;
      case 'a':                                               //Turn Left
//        servo1.write(45);
//        servo2.write(45);
        delay(5);
        turn_L (255,255);
        break;
      case 'd':                                               //Turn Right
//        servo1.write(135);
//        servo2.write(135);
        delay(5);
        turn_R (255,255);
        break;
      case 'x':
        stop();
        break;
      }
    }
    else stop();
  }
 }
 

void PWM_Mode_Setup(){
  pinMode(URTRIG,OUTPUT);                                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                                  // Set to HIGH

  pinMode(URPWM, INPUT);                                      // Sending Enable PWM mode command

  for(int i=0;i<4;i++)
    Serial.write(EnPwmCmd[i]);
}

void PWM_Mode(){                                              // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);                                 // reading Pin PWM will output pulses

  unsigned long DistanceMeasured=pulseIn(URPWM,LOW);

  if(DistanceMeasured==50000)                                 // the reading is invalid.
    Serial.print("Invalid");
  else
    Distance=DistanceMeasured/50;                             // every 50us low level stands for 1cm
}
