#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
//#include <Servo.h>

//Servo servo1;
//Servo servo2;
//Servo servo3;

#define baserotationpwm 6
#define basedirection 7
#define bevel_right_pwm 18
#define bevel_right_drn 5
#define bevel_left_pwm  17
#define bevel_left_drn  16
#define DIR4 19  // GPIO 26
#define PWM4 21  // GPIO 27
#define DIR6 22  // GPIO 13
#define PWM6 23  // GPIO 12
#define POT1 34  // GPIO 34

#define servo1pin 9
#define servo2pin 8
#define servo3pin 7
#define stepperenablepin 3  // GPIO 3

const int dirPin = 4; // can be 4 and 3 as well
const int stepPin = 11; // can be 11 and 2 as well
int stepp=0;
const int stepsPerRevolution = 50;

ros::NodeHandle n;
std_msgs::Int16MultiArray msg;

int vel1;
int vel2;
int var;
int var_base;
int var_bev;
int var_st;
int vel_base;
int vel_bev;

void messageCallback(const std_msgs::Int16MultiArray& receivedMsg) {
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

  var_base = receivedMsg.data[3];
  var_bev = receivedMsg.data[5];
  var_st = receivedMsg.data[7];

  vel_base = receivedMsg.data[4];
  if (receivedMsg.data[4] > 25 && receivedMsg.data[4] < 175) {
    vel_base = receivedMsg.data[4];
  } else {
    vel_base = 0;
  }

  vel_bev = receivedMsg.data[6];
  if (receivedMsg.data[6] > 25 && receivedMsg.data[6] < 175) {
    vel_bev = receivedMsg.data[6];
  } else {
    vel_bev = 0;
  }
}

void control_things(){

  if(receivedMsg.data[0] == 0 && receivedMsg.data[1] == 0){
    analogWrite(PWM4, 0);
    analogWrite(PWM6, 0);
    
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, LOW);
  }
  if(receivedMsg.data[0] >= 0 && receivedMsg.data[1] >= 0){
    analogWrite(PWM4, abs(vel_la1));     
    analogWrite(PWM6, abs(vel_la2));  //linear actuators 1 and 2 extend
    digitalWrite(DIR4, HIGH);
    digitalWrite(DIR6, HIGH);
  }
  if(receivedMsg.data[0] <= 0 && receivedMsg.data[1] <= 0){
    analogWrite(PWM4, abs(vel_la1));
    analogWrite(PWM6, abs(vel_la2));  //linear actuators 1 and 2 retract 
    digitalWrite(DIR4, LOW);
    digitalWrite(DIR6, LOW);
  }
  if(receivedMsg.data[0] <= 0 && receivedMsg.data[1] >= 0){
    analogWrite(PWM4, abs(vel_la1));
    analogWrite(PWM6, abs(vel_la2));  //linear actuator 1 extends and linear actuator 2 retracts
    digitalWrite(DIR4 , LOW);
    digitalWrite(DIR6, HIGH);
  }
  if(receivedMsg.data[0] >= 0 && receivedMsg.data[1] <= 0){
    analogWrite(PWM4, abs(vel_la1));
    analogWrite(PWM6, abs(vel_la2));  //linear actuator 1 retracts and linear actuator 2 extends
    digitalWrite(DIR4, HIGH);
    digitalWrite(DIR6, LOW);
  }

  if (var_st == 1) {
    digitalWrite(stepperenablepin, HIGH);  // Enable stepper motor
  } else if (var_st == 2) {
    digitalWrite(stepperenablepin, LOW);   // Disable stepper motor
  }

  if(var_base == 0 && var_bev == 0 && var_st == 0){
    digitalWrite(baserotationpwm, LOW);//off
    digitalWrite(bevel_right_pwm, LOW);
    digitalWrite(bevel_left_pwm, LOW);
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, LOW);
  }
  if(var_base == 1){
    digitalWrite(basedirection, HIGH);//base rotates in one direction
    analogWrite(baserotationpwm, vel_base);
    digitalWrite(bevel_right_pwm, LOW);
    digitalWrite(bevel_left_pwm, LOW);
  }
  if(var_base == 2){
    digitalWrite(basedirection, LOW);//base rotates in another direction
    analogWrite(baserotationpwm, vel_base);
    digitalWrite(bevel_right_pwm, LOW);
    digitalWrite(bevel_left_pwm, LOW);
  }

  if(var_bev == 1){
    digitalWrite(bevel_right_drn, LOW);//gripper roll motion in one direction
    digitalWrite(bevel_left_drn, HIGH);
    analogWrite(bevel_right_pwm, vel_bev);
    analogWrite(bevel_left_pwm, vel_bev);
    digitalWrite(baserotationpwm, LOW);
  }
  if(var_bev == 2){
    digitalWrite(bevel_right_drn, HIGH);//gripper roll motion in another direction
    digitalWrite(bevel_left_drn, LOW);
    analogWrite(bevel_right_pwm, vel_bev);
    analogWrite(bevel_left_pwm, vel_bev);
    digitalWrite(baserotationpwm, LOW);
  }
  if(var_bev == 3){
    digitalWrite(bevel_right_drn, HIGH);//gripper pitch motion in one direction
    digitalWrite(bevel_left_drn, HIGH);
    analogWrite(bevel_right_pwm, vel_bev);
    analogWrite(bevel_left_pwm, vel_bev);
    digitalWrite(baserotationpwm, LOW);
  }
  if(var_bev == 4){
    digitalWrite(bevel_right_drn, LOW);//gripper pitch motion in another direction
    digitalWrite(bevel_left_drn, LOW);
    analogWrite(bevel_right_pwm, vel_bev);  
    analogWrite(bevel_left_pwm, vel_bev);
    digitalWrite(baserotationpwm, LOW);
  }

  if(var_st == 1){
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
  }
}

ros::Subscriber<std_msgs::Int16MultiArray> sub1("/control", messageCallback);

void setup() {
  pinMode(DIR4, OUTPUT);
  pinMode(PWM4, OUTPUT);
  pinMode(DIR6, OUTPUT);
  pinMode(PWM6, OUTPUT);
  pinMode(POT1, INPUT);
  pinMode(stepperenablepin, OUTPUT);
  pinMode(baserotationpwm,OUTPUT);
  pinMode(basedirection,OUTPUT);
  pinMode(bevel_right_pwm,OUTPUT);
  pinMode(bevel_left_pwm,OUTPUT);
  pinMode(bevel_right_drn,OUTPUT);
  pinMode(bevel_left_drn,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);
  digitalWrite(3, LOW);

  //servo3.attach(servo3pin);
  //servo2.attach(servo2pin);

  n.initNode();
  n.subscribe(sub1);
}

void loop() {
  control_things();
  n.spinOnce();
}
