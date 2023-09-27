#include <ros.h>
#include <std_msgs/Int8.h>


int L_DirPin = 8;
int L_PWM_Pin = 9;
int R_Dir_Pin = 12;
int R_PWM_Pin = 11;

int 1_DirPin = 2;
int 1_PWM_Pin = 3;
int 2_Dir_Pin = 4;
int 2_PWM_Pin = 5;

int Stepper_Dir = x;
int Stepper_PWM = y;

int Speed = 80;

ros::NodeHandle nh;

void messageCb_bevel(const std_msgs::Int8& toggle_msg) {
  input_bevel= toggle_msg.data;
  input_stepper = toggle_msg.data;
}
void messageCb_act(const std_msgs::Int8& toggle_msg) {
  input_act= toggle_msg.data;
}

ros::Subscriber<std_msgs::Int8> sub_bevel("/controls_bevel_stepper", &messageCb_bevel);
ros::Subscriber<std_msgs::Int8> sub_act("/controls_act", &messageCb_act);


void setup() {
  nh.initNode();
  nh.subscribe(sub_bevel);
  nh.subscribe(sub_act);

  pinMode(L_PWM_Pin, OUTPUT);
  pinMode(L_DirPin, OUTPUT);
  pinMode(R_PWM_Pin, OUTPUT);
  pinMode(R_Dir_Pin, OUTPUT);

  pinMode(1_PWM_Pin, OUTPUT);
  pinMode(1_DirPin, OUTPUT);
  pinMode(2_PWM_Pin, OUTPUT);
  pinMode(2_Dir_Pin, OUTPUT); 

  pinMode(Stepper_Dir,OUTPUT);
  pinMode(Stepper_PWM,OUTPUT);
}

void controlling(Dir_Pin,PWM_Pin,Status,PWM_Speed){
  digitalWrite(Dir_Pin,Status);
  AnalogWrite(PWM_Pin,PWM_Speed);
}

void loop() {
  if 
  switch (input_bevel) {
    case 1:
      controlling(L_Dir_Pin,L_PWM_Pin,LOW,Speed);
      controlling(R_Dir_Pin,R_PWM_Pin,LOW,Speed)
      break;
    case 2:
      controlling(L_Dir_Pin,L_PWM_Pin,HIGH,Speed);
      controlling(R_Dir_Pin,R_PWM_Pin,HIGH,Speed);
      break;
    case 3:
      controlling(L_Dir_Pin,L_PWM_Pin,LOW,Speed);
      controlling(R_Dir_Pin,R_PWM_Pin,HIGH,Speed);
      break;
    case 4:
      controlling(L_Dir_Pin,L_PWM_Pin,HIGH,Speed);
      controlling(R_Dir_Pin,R_PWM_Pin,LOW,Speed);
      break;
    case 0:
      controlling(L_Dir_Pin,L_PWM_Pin,LOW,0);
      controlling(R_Dir_Pin,R_PWM_Pin,LOW,0);
      break;
    
  }
  if
  switch (input_act){
    case 1:
      controlling(1_Dir_Pin,1_PWM_Pin,LOW,Speed);
      break;
    case 2:
      controlling(1_Dir_Pin,1_PWM_Pin,HIGH,Speed);
      break;
    case 3:
      controlling(2_Dir_Pin,2_PWM_Pin,LOW,Speed);
      break;
    case 4:
      controlling(2_Dir_Pin,2_PWM_Pin,HIGH,Speed);
      break;
    case 0:
      controlling(1_Dir_Pin,1_PWM_Pin,LOW,0);
      controlling(2_Dir_Pin,2_PWM_Pin,LOW,0);
      break;
  }
  if
  switch(input_stepper){
    case 5:
      controlling(Stepper_Dir,Stepper_PWM,LOW,Speed);
      break;
    case 6:
      controlling(Stepper_Dir,Stepper_PWM,HIGH,Speed);
      break;
    case 7:
      controlling(Stepper_Dir,Stepper_PWM,LOW,0);
      break;
  }
  nh.spinOnce();
  delay(1);
}
