#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
#include<geometry_msgs/Point.h>
#include <Servo.h>

Servo s1;
Servo s2;
int x,y,z;

#define DIR4 6               //connections to be checked
#define PWM4 5
#define DIR6 10                   //1 6inch 2 4inch
#define PWM6 11
#define POT1 A4

#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
#define servo4pin 4

#define stepperenablepin 3

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;

int vel;
void messageCallback(const std_msgs::Int16MultiArray& receivedMsg)
{
  int vel_la1 = receivedMsg.data[0];
  if (abs(receivedMsg.data[0]) > 50) {
    vel_la1 = receivedMsg.data[0];
  } else {
    vel_la1 = 0;
  }

  int vel_la2 = receivedMsg.data[1];
  if (abs(receivedMsg.data[1]) > 50) {
    vel_la2 = receivedMsg.data[1];
  } else {
    vel_la2 = 0;
  }

  int var_st = receivedMsg.data[2];

  if(receivedMsg.data[0]== 0 && receivedMsg.data[1] == 0){
    analogWrite(PWM4, 0);
    analogWrite(PWM6, 0);
    
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, LOW);
  }

  if(receivedMsg.data[0]> 0){
    analogWrite(PWM4, abs(vel_la1));
    digitalWrite(DIR4, HIGH);
  }
  if(receivedMsg.data[0]<0){
    analogWrite(PWM4, abs(vel_la1));
    digitalWrite(DIR4, LOW);
  }
  if(receivedMsg.data[1]> 0){
    analogWrite(PWM6, abs(vel_la2));
    digitalWrite(DIR6, HIGH);
  }
  if(receivedMsg.data[1]<0){
    analogWrite(PWM6, abs(vel_la2));
    digitalWrite(DIR6, LOW);
  }

  if(var_st == 1){
    digitalWrite(stepperenablepin,LOW);
  }
  else if(var_st == 2){
    digitalWrite(stepperenablepin,HIGH);
  }
}

void callback(const geometry_msgs::Point &msg){
  x=msg.x;
  y=msg.y;
  if(x!=0){
    s1.write(90+x*65);
    delay(200);
    s1.write(90);
  }
  if(y!=0){
    s2.write(90+y*65);
    delay(90);
    s2.write(105);
    
    }
}

ros::Subscriber<std_msgs::Int16MultiArray> sub1("/control1", messageCallback); 
ros::Subscriber<geometry_msgs::Point> sub("cam_gimble",&callback);


void setup(){
  pinMode(DIR4,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(DIR6,OUTPUT);
  pinMode(PWM6,OUTPUT);
  pinMode(POT1,INPUT);
  s1.attach(7);
  s2.attach(8);
  digitalWrite(stepperenablepin, LOW);
  pinMode(3,OUTPUT);
  n.initNode();
  n.subscribe(sub1);
}

void loop(){
  s1.write(90);
  s2.write(90);
  n.subscribe(sub);
  n.advertise(pub);
  n.spinOnce();
}


