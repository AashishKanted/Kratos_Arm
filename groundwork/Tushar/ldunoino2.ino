#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>

#define DIR4 5               //connections to be checked
#define PWM4 10
#define DIR5 7                   //1 6inch 2 4inch
#define PWM5 6
#define DIR6 12
#define PWM6 9

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;

void messageCallback(const std_msgs::Int16MultiArray& receivedMsg)
{
  
  int var_pump2 = receivedMsg.data[1];
  int var_pump3 = receivedMsg.data[2];
  int var_auger_spin = receivedMsg.data[0];

  if(receivedMsg.data[0]== 0 && receivedMsg.data[1] == 0 && receivedMsg.data[2] == 0){
    digitalWrite(PWM4, 0);
    digitalWrite(PWM5, 0);
    digitalWrite(PWM6, 0);
    digitalWrite(DIR4, 0);
    digitalWrite(DIR5, 0);
    digitalWrite(DIR6, 0);
  }
  if(receivedMsg.data[0] == 1){
    digitalWrite(PWM4, HIGH);     
    digitalWrite(DIR4, HIGH);
  }
  if(receivedMsg.data[0] == -1){
    digitalWrite(PWM4, HIGH);     
    digitalWrite(DIR4, LOW);
  }
  if(receivedMsg.data[1] == 1){
    digitalWrite(PWM5, HIGH);
    digitalWrite(DIR5, HIGH);
  }
  if(receivedMsg.data[1] == -1){
    digitalWrite(PWM5, HIGH);
    digitalWrite(DIR5, LOW);
  }
  if(receivedMsg.data[2] == 1){
    digitalWrite(PWM6, HIGH);
    digitalWrite(DIR6, HIGH);
  }
}

ros::Subscriber<std_msgs::Int16MultiArray> sub1("/lduno_topic", messageCallback); 

void setup(){
  pinMode(DIR4,OUTPUT);
  pinMode(PWM4,OUTPUT);
  pinMode(DIR5,OUTPUT);
  pinMode(PWM5,OUTPUT);
  pinMode(DIR6,OUTPUT);
  pinMode(PWM6,OUTPUT);

  n.initNode();
  n.subscribe(sub1);
}

void loop(){
  n.spinOnce();
}