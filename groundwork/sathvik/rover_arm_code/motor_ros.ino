
#include <ros.h>
#include <std_msgs/Int8.h>

ros::NodeHandle nh;

int pwm_pin = 9;
int dir_pin = 6;

void messageCb(const std_msgs::Int8& toggle_msg) {
  int input = toggle_msg.data;
  if (input==1){
    /* digitalWrite(dir_pin, HIGH);
    analogWrite(pwm_pin, 50);*/
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (input==2){
    /*digitalWrite(dir_pin, LOW);
    analogWrite(pwm_pin, 50);*/
    digitalWrite(LED_BUILTIN, LOW);
  }
  /*else if (input==3){
    digitalWrite(dir_pin, LOW);
    analogWrite(pwm_pin, 0);
  }*/
} 

ros::Subscriber<std_msgs::Int8> sub("chatter", messageCb);

void setup() {
  // put your setup code here, to run once:
  /*pinMode(pwm_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);*/
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);

}

void loop(){
  nh.spinOnce();
  delay(500);
}