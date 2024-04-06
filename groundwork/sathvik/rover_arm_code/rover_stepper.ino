#include <ros.h>
#include<std_msgs/Int8.h>

const int stepPin = 5;
const int dirPin = 4;
const int enPin = 2;

int stepper;

ros::NodeHandle nh;

void message_stepper(const std_msgs::Int8& toggle_msg){
  stepper = toggle_msg.data;
}

ros::Subscriber<std_msgs::Int8> sub_step("controls_stepper", message_stepper);

void setup() {

  nh.initNode();
  nh.subscribe(sub_step);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  
  digitalWrite(enPin, LOW); // active low
}

void loop(){
  switch(stepper){
    case 1:
      digitalWrite(dirPin, HIGH);
      for(int x=0; x<50; x++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
      stepper = 0;
      break;
    
    case 2:
      digitalWrite(dirPin, LOW);
      for(int x=0; x<50; x++){
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
      stepper = 0;
      break;
    
    case 0:
      digitalWrite(stepPin, LOW);
      break;
  }
  nh.spinOnce();
}
