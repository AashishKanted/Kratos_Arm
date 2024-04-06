#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>

#define DIR1 6               //connections to be checked
#define PWM1 5
#define DIR2 10                   //1 6inch 2 4inch
#define PWM2 11
#define DIR3 12
#define PWM3 1

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;

void messageCallback(const std_msgs::Int16MultiArray& receivedMsg)
{
  
  int var_pump2 = receivedMsg.data[1];
  int var_pump3 = receivedMsg.data[2];
  int var_auger_spin = receivedMsg.data[0];

  if(receivedMsg.data[0]== 0 && receivedMsg.data[1] == 0 && receivedMsg.data[2] == 0){
    digitalWrite(PWM1, 0);
    digitalWrite(PWM2, 0);
    digitalWrite(PWM3, 0);
    digitalWrite(DIR1, 0);
    digitalWrite(DIR2, 0);
    digitalWrite(DIR3, 0);
  }
  if(receivedMsg.data[0] == 1){
    digitalWrite(PWM1, HIGH);     
    digitalWrite(DIR1, HIGH);
  }
  if(receivedMsg.data[0] == -1){
    digitalWrite(PWM1, HIGH);     
    digitalWrite(DIR1, LOW);
  }
  if(receivedMsg.data[1] == 1){
    digitalWrite(PWM2, HIGH);
    digitalWrite(DIR2, HIGH);
  }
  if(receivedMsg.data[2] == 1){
    digitalWrite(PWM3, HIGH);
    digitalWrite(DIR3, HIGH);
  }
}

ros::Subscriber<std_msgs::Int16MultiArray> sub1("/ldmega_topic", messageCallback); 

void setup(){
  pinMode(DIR1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(DIR3,OUTPUT);
  pinMode(PWM3,OUTPUT);

  n.initNode();
  n.subscribe(sub1);
}

void loop(){
  n.spinOnce();
}
