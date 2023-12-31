#include <ros.h>
#include<std_msgs/Int8.h>
#include<std_msgs/Int64.h>

// bevels
const int DirPin_1 = 12;
const int DirPin_2 = 13;
const int PWM_1 = 10;
const int PWM_2 = 11;

// actuators
const int DirPin_3 = 7;
const int DirPin_4 = 4;
const int PWM_3 = 3;
const int PWM_4 = 5;

int bevel;
int actuator;

ros::NodeHandle nh;

void message_bevel(const std_msgs::Int8& toggle_msg){
  bevel = toggle_msg.data;
}

void message_act(const std_msgs::Int64& toggle_msg){
  actuator = toggle_msg.data;
}

ros::Subscriber<std_msgs::Int8> sub_bevel("controls_bevel", message_bevel);
ros::Subscriber<std_msgs::Int64> sub_act("controls_act", message_act);

void setup() {
  
  pinMode(DirPin_1, OUTPUT);
  pinMode(DirPin_2, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  
  pinMode(DirPin_3, OUTPUT);
  pinMode(DirPin_4, OUTPUT);
  pinMode(PWM_3, OUTPUT);
  pinMode(PWM_4, OUTPUT);

  nh.initNode();
  nh.subscribe(sub_bevel);
  nh.subscribe(sub_act);
}

void loop() {
  
  // bevel motors
  if(bevel == 0){
    digitalWrite(PWM_1,LOW);
    digitalWrite(PWM_2,LOW);
    digitalWrite(DirPin_1,LOW);
    digitalWrite(DirPin_2,LOW);
  }
  else if(bevel == 1){
    digitalWrite(PWM_1,HIGH);
    digitalWrite(PWM_2,HIGH);
    digitalWrite(DirPin_1,HIGH);
    digitalWrite(DirPin_2,HIGH);    
  }
  else if(bevel == 2){
    digitalWrite(PWM_1,HIGH);
    digitalWrite(PWM_2,HIGH);
    digitalWrite(DirPin_1,LOW);
    digitalWrite(DirPin_2,LOW);    
  }
  else if(bevel == 3){
    digitalWrite(PWM_1,HIGH);
    digitalWrite(PWM_2,HIGH);
    digitalWrite(DirPin_1,HIGH);
    digitalWrite(DirPin_2,LOW);    
  }
  else if(bevel == 4){
    digitalWrite(PWM_1,HIGH);
    digitalWrite(PWM_2,HIGH);
    digitalWrite(DirPin_1,LOW);
    digitalWrite(DirPin_2,HIGH);    
  }

  // actuator
  if(actuator>255){
    analogWrite(PWM_3, actuator-255);
    digitalWrite(DirPin_3,HIGH);   
  }
  else if(actuator<-255){
    analogWrite(PWM_3, (-1)*(actuator+255));
    digitalWrite(DirPin_3,LOW);   
  }
  else if(actuator>0){
    analogWrite(PWM_4, actuator);
    digitalWrite(DirPin_4,HIGH);  
  }
  else if(actuator<0){
    analogWrite(PWM_4, (-1)*actuator);
    digitalWrite(DirPin_4,LOW);   
  }
  else {
    digitalWrite(PWM_3,LOW);
    digitalWrite(PWM_4,LOW);
    digitalWrite(DirPin_3,LOW);
    digitalWrite(DirPin_4,LOW);
  }

  nh.spinOnce();
}
