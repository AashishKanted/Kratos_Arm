#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
//Servo servo4;

#define DIR4 6               //connections to be checked
#define PWM4 5
#define DIR6 10                   //1 6inch 2 4inch
#define PWM6 11
#define POT1 A4

#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
//#define servo4pin 4

#define stepperenablepin 3

//float servo11,servo22,servo33;
//int servofun1=0;
//int servofun2=0;

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;

//ros::Publisher pub1("velocitiesm", &vels);
int vel,var;
void messageCallback(const std_msgs::Int16MultiArray& receivedMsg)
{
  int var = receivedMsg.data[0];
  if (receivedMsg.data[1] > 50) {
    vel = receivedMsg.data[1];
  } else {
    vel = 0;
  }

  if(var == 0){
    analogWrite(PWM4, LOW);
    analogWrite(PWM6, LOW);
    
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, LOW);
  }
  else if(var == 1){
    analogWrite(PWM4, vel);     //pwmpin3 = PWM4, pwmpin4 = PWM6
    digitalWrite(PWM6, LOW);
    digitalWrite(DIR4, HIGH);
  }
  else if(var == 2){
    analogWrite(PWM4, vel);
    digitalWrite(PWM6, LOW);
    digitalWrite(DIR4, LOW);
  }
  else if(var == 3){
    digitalWrite(PWM4, LOW);
    analogWrite(PWM6, vel);
    digitalWrite(DIR6, HIGH);
  }
  else if(var == 4){
    digitalWrite(PWM4, LOW);
    analogWrite(PWM6, vel);
    digitalWrite(DIR6, LOW);
  }

  if(var==5){
    digitalWrite(stepperenablepin,LOW);
  }
  else if(var==6){
    digitalWrite(stepperenablepin,HIGH);
  }
}
/* if(value_passed==3){
    servo3.write(105);
    delay(200);
    servo3.write(90);
  }
  else if(value_passed==-3){
    servo3.write(75);
    delay(200);
    servo3.write(90);
  }
  else{
    servo3.write(90);
  }
  if(value_passed==4){
    servo2.write(105);
    delay(200);
    servo2.write(90);
  }
  else if(value_passed==-4){
    servo2.write(75);
    delay(200);
    servo2.write(90);
  }
  else{
    servo2.write(90);
  }
//  

//    vels.data=vel1;
//  vels.angular.y=vel2;
//  vels.linear.x=servofun1;
//  vels.linear.y=servofun2;
}*/

ros::Subscriber<std_msgs::Int16MultiArray> sub1("/control1", messageCallback); 

void setup(){
  pinMode(DIR4,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(DIR6,OUTPUT);
  pinMode(PWM6,OUTPUT);
  pinMode(POT1,INPUT);
  servo3.attach(7);
  servo2.attach(8);

  pinMode(3,OUTPUT);
  n.initNode();
  n.subscribe(sub1);
//  n.advertise(pub1);
}

void loop(){
  
//  pub1.publish(&vels);
  n.spinOnce();
}
