#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#define DIR1 5
#define PWM1 10
#define DIR_EL 7
#define PWM_EL 6
#define DIR_MIX 12
#define PWM_MIX 9
std_msgs::Int16MultiArray str_msg;
ros::NodeHandle nh;

void messageCb( const std_msgs::Int16MultiArray& msg){
  if(msg.data[0]==1){
    analogWrite(PWM1,255);//use peristaltic pump 1
  }
  else if(msg.data[1]==1){
    digitalWrite(DIR_EL,HIGH);
    analogWrite(PWM_EL,255);//bring the auger up/down
  }
  else if(msg.data[2]==1){
    digitalWrite(DIR_EL,LOW);
    analogWrite(PWM_EL,255);//bring auger down/up
  }
  else if(msg.data[3]==1){
    digitalWrite(DIR_MIX,HIGH);
    analogWrite(PWM_MIX,255);//rotate mixing chamber clock
  }
  else if(msg.data[4]==1){
    digitalWrite(DIR_MIX,LOW);
    analogWrite(PWM_MIX,255);//rotate mixing chamber anti clock
  }
  else{
    analogWrite(PWM1,0);
    analogWrite(PWM_EL,0);
    analogWrite(PWM_MIX,0);//make sure everything is switched off 
  }
}
ros::Subscriber<std_msgs::Int16MultiArray> sub("/control2", &messageCb );
void setup() {
  nh.initNode();
  nh.subscribe(sub);

  // put your setup code here, to run once:
  pinMode(DIR1,OUTPUT);
  pinMode(PWM1,OUTPUT);
  digitalWrite(DIR1,HIGH);//peristaltic pump 1

  pinMode(DIR_EL,OUTPUT);
  pinMode(PWM_EL,OUTPUT);//Motor used to make auger go up or down.

  pinMode(DIR_MIX,OUTPUT);
  pinMode(PWM_MIX,OUTPUT);//motor used for mixing chamber.

}

void loop() {
  nh.spinOnce();
  //delay(1);
  
  
} 
