#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
//#include <Servo.h>

//Servo servo1;
//Servo servo2;
//Servo servo3;

#define baserotationpwm 15
#define basedirection 5
#define bevel_right_pwm 14
#define bevel_right_drn 12
#define bevel_left_pwm  25
#define bevel_left_drn  26
#define DIR4 33
#define PWM4 32
#define DIR6 4
#define PWM6 0
#define gripperpwm 13
#define gripperdir 27

//#define servo1pin 9
//#define servo2pin 8
//#define servo3pin 7

/*const int dirPin = 4; // can be 4 and 3 as well
const int stepPin = 11; // can be 11 and 2 as well
int stepp=0;
const int stepsPerRevolution = 50;*/

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;
ros::Publisher chatter("chatter", &msg);

int vel1;
int vel2;
int var;
int vel_la1;
int vel_la2;
int var_base;
int var_bev;
int vel_base;
int vel_bev;
int var_gripper;

void messageCallback(const std_msgs::Int16MultiArray& receivedMsg) {
  vel_la1 = receivedMsg.data[0];
  if (abs(receivedMsg.data[0]) > 50) {
    vel_la1 = receivedMsg.data[0];
  } else {
    vel_la1 = 0;
  }

  vel_la2 = receivedMsg.data[1];
  if (abs(receivedMsg.data[1]) > 50) {
    vel_la2 = receivedMsg.data[1];
  } else {
    vel_la2 = 0;
  }

  vel_base = receivedMsg.data[3];
  if (receivedMsg.data[3] > 25 && receivedMsg.data[3] < 175) {
    vel_base = receivedMsg.data[3];
  } else {
    vel_base = 0;
  }

  vel_bev = receivedMsg.data[5];
  if (receivedMsg.data[5] > 25 && receivedMsg.data[5] < 176) {
    vel_bev = receivedMsg.data[5];
  } else {
    vel_bev = 0;
  }

  if(receivedMsg.data[0] == 0 && receivedMsg.data[1] == 0){
    analogWrite(PWM4, 0);
    analogWrite(PWM6, 0);
    
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, LOW);
  }
  else if(receivedMsg.data[0] >= 0 && receivedMsg.data[1] >= 0){
    analogWrite(PWM4, abs(vel_la1));     
    analogWrite(PWM6, abs(vel_la2));  //linear actuators 1 and 2 extend
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, LOW);
  }
  else if(receivedMsg.data[0] <= 0 && receivedMsg.data[1] <= 0){
    analogWrite(PWM4, abs(vel_la1));
    analogWrite(PWM6, abs(vel_la2));  //linear actuators 1 and 2 retract 
    digitalWrite(DIR4, HIGH);
    digitalWrite(DIR6, HIGH);
  }
  else if(receivedMsg.data[0] <= 0 && receivedMsg.data[1] >= 0){
    analogWrite(PWM4, abs(vel_la1));
    analogWrite(PWM6, abs(vel_la2));  //linear actuator 1 extends and linear actuator 2 retracts
    digitalWrite(DIR4, HIGH);
    digitalWrite(DIR6, LOW);
  }
  else if(receivedMsg.data[0] >= 0 && receivedMsg.data[1] <= 0){
    analogWrite(PWM4, abs(vel_la1));
    analogWrite(PWM6, abs(vel_la2));  //linear actuator 1 retracts and linear actuator 2 extends
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, HIGH);
  }


  if(receivedMsg.data[2] == 0){
    digitalWrite(baserotationpwm, 0);//off
  }

  if(receivedMsg.data[4] == 0) {
    digitalWrite(bevel_right_pwm, 0);
    digitalWrite(bevel_left_pwm, 0);
    //msg.data = 0;
  }

  if(receivedMsg.data[6] == 0) {
    digitalWrite(gripperpwm, 0);
  }
  if(receivedMsg.data[2] == 1){
    digitalWrite(basedirection, HIGH);//base rotates in one direction
    analogWrite(baserotationpwm, vel_base);
  }
  if(receivedMsg.data[2] == 2){
    digitalWrite(basedirection, LOW);//base rotates in another direction
    analogWrite(baserotationpwm, vel_base);
  }

  if(receivedMsg.data[4] == 1){
    digitalWrite(bevel_right_drn, LOW);//gripper roll motion in one direction
    digitalWrite(bevel_left_drn, HIGH);
    analogWrite(bevel_right_pwm, vel_bev);
    analogWrite(bevel_left_pwm, vel_bev);
  }
  if(receivedMsg.data[4] == 2){
    digitalWrite(bevel_right_drn, HIGH);//gripper roll motion in another direction
    digitalWrite(bevel_left_drn, LOW);
    analogWrite(bevel_right_pwm, vel_bev);
    analogWrite(bevel_left_pwm, vel_bev);
  }
  if(receivedMsg.data[4] == 3){
    digitalWrite(bevel_right_drn, HIGH);//gripper pitch motion in one direction
    digitalWrite(bevel_left_drn, HIGH);
    analogWrite(bevel_right_pwm, vel_bev);
    analogWrite(bevel_left_pwm, vel_bev);
  }
  if(receivedMsg.data[4] == 4){
    digitalWrite(bevel_right_drn, LOW);//gripper pitch motion in another direction
    digitalWrite(bevel_left_drn, LOW);
    analogWrite(bevel_right_pwm, vel_bev);  
    analogWrite(bevel_left_pwm, vel_bev);
  }

  if (receivedMsg.data[6] == 1) {
    digitalWrite(gripperdir, HIGH);
    analogWrite(gripperpwm, 125);
  }

  if (receivedMsg.data[6] == 2) {
    digitalWrite(gripperdir, LOW);
    analogWrite(gripperpwm, 125);
  }
  if (receivedMsg.data[6] == 0){
    analogWrite(gripperpwm, 0);
  }

  chatter.publish(&msg);

  /*if(var_st == 1){
    digitalWrite(dirPin, HIGH);
    
    for(int x=0; x<5; x++){
      
      digitalWrite(stepPin, HIGH);//gripper opens or closes
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }
  else if(var_st == 2){
    digitalWrite(dirPin, LOW);
    
    for(int x=0; x<5; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  }*/
}

//void control_things(){}

ros::Subscriber<std_msgs::Int16MultiArray> sub1("/control", messageCallback);

void setup() {
  pinMode(DIR4, OUTPUT);
  pinMode(PWM4, OUTPUT);
  pinMode(DIR6, OUTPUT);
  pinMode(PWM6, OUTPUT);
  pinMode(baserotationpwm,OUTPUT);
  pinMode(basedirection,OUTPUT);
  pinMode(bevel_right_pwm,OUTPUT);
  pinMode(bevel_left_pwm,OUTPUT);
  pinMode(bevel_right_drn,OUTPUT);
  pinMode(bevel_left_drn,OUTPUT);
  pinMode(gripperdir,OUTPUT);
  pinMode(gripperpwm,OUTPUT);

  pinMode(PWM4, LOW);
  pinMode(PWM6, LOW);
  pinMode(baserotationpwm, LOW);
  pinMode(bevel_right_pwm, LOW);
  pinMode(bevel_left_pwm, LOW);
  pinMode(gripperpwm, LOW);



  //servo3.attach(servo3pin);
  //servo2.attach(servo2pin);

  n.initNode();
  n.subscribe(sub1);
  n.advertise(chatter);
}

void loop() {
  //control_things();
  n.spinOnce();
}
