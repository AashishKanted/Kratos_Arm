#include <ros.h>
#include <std_msgs/Int16MultiArray.h>

#define baserotationpwm 6
#define basedirection 7
#define bevel_right_pwm 10
#define bevel_right_drn 5
#define bevel_left_pwm  9
#define bevel_left_drn  12
const int dirPin = 4; // can be 4 and 3 as well
const int stepPin = 11; // can be 11 and 2 as well
int stepp=0;
const int stepsPerRevolution = 5;

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;

int vel,var;
void messageCallback(const std_msgs::Int16MultiArray& receivedMsg)
{
  int var = receivedMsg.data[0];
  if (receivedMsg.data[1] > 10) {
    vel = receivedMsg.data[1];
  } else {
    vel = 0;
  }

  if(var==0){
    digitalWrite(baserotationpwm, LOW);//off
    digitalWrite(bevel_right_pwm, LOW);
    digitalWrite(bevel_left_pwm, LOW);
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);
  }
  else if(var==1){
    digitalWrite(basedirection, HIGH);//base rotates in one direction
    analogWrite(baserotationpwm, vel);
    digitalWrite(bevel_right_pwm, LOW);
    digitalWrite(bevel_left_pwm, LOW);
  }
  else if(var==2){
    digitalWrite(basedirection, LOW);//base rotates in another direction
    analogWrite(baserotationpwm, vel);
    digitalWrite(bevel_right_pwm, LOW);
    digitalWrite(bevel_left_pwm, LOW);
  }
  else if(var==3){
    digitalWrite(bevel_right_drn, LOW);//gripper roll motion in one direction
    digitalWrite(bevel_left_drn, HIGH);
    analogWrite(bevel_right_pwm, vel);
    analogWrite(bevel_left_pwm, vel);
    digitalWrite(baserotationpwm, LOW);
  }
  else if(var==4){
    digitalWrite(bevel_right_drn, HIGH);//gripper roll motion in another direction
    digitalWrite(bevel_left_drn, LOW);
    analogWrite(bevel_right_pwm, vel);
    analogWrite(bevel_left_pwm, vel);
    digitalWrite(baserotationpwm, LOW);
  }
  else if(var==5){
    digitalWrite(bevel_right_drn, HIGH);//gripper pitch motion in one direction
    digitalWrite(bevel_left_drn, HIGH);
    analogWrite(bevel_right_pwm, vel);
    analogWrite(bevel_left_pwm, vel);
    digitalWrite(baserotationpwm, LOW);
  }
  else if(var==6){
    digitalWrite(bevel_right_drn, LOW);//gripper pitch motion in another direction
    digitalWrite(bevel_left_drn, LOW);
    analogWrite(bevel_right_pwm, vel);  
    analogWrite(bevel_left_pwm, vel);
    digitalWrite(baserotationpwm, LOW);
  }
  else if(var==7){
    digitalWrite(dirPin, HIGH);
    
    for(int x=0; x<stepsPerRevolution; x++){
      digitalWrite(stepPin, HIGH);//gripper opens or closes
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }
  else if(var==8){
    digitalWrite(dirPin, LOW);
    
    for(int x=0; x<stepsPerRevolution; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }
}
ros::Subscriber<std_msgs::Int16MultiArray> sub1("/control2", messageCallback); 
void setup(){
  pinMode(baserotationpwm,OUTPUT);
  pinMode(basedirection,OUTPUT);
  pinMode(bevel_right_pwm,OUTPUT);
  pinMode(bevel_left_pwm,OUTPUT);
  pinMode(bevel_right_drn,OUTPUT);
  pinMode(bevel_left_drn,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);

  n.initNode();
  n.subscribe(sub1);
}

void loop(){
  n.spinOnce();
}
