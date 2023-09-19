/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
// #include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>
// #include <std_msgs/String.h>


int direction_pin = 6;
int pwn_pin = 9;

ros::NodeHandle  nh;

std_msgs::Int8 new_msg;

ros::Publisher publish_data("/modified_data", &new_msg);

int8_t input_command;
bool to_publish = false;

void messageCb( const std_msgs::Int8& toggle_msg){
  
  input_command = toggle_msg.data;
  to_publish = true;


  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
}

ros::Subscriber<std_msgs::Int8> sub("/control_motor", &messageCb );

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(publish_data);

  pinMode(pwn_pin, OUTPUT);
  pinMode(direction_pin, OUTPUT);
}


void go_forward(){
  digitalWrite(direction_pin, LOW);

  analogWrite(pwn_pin, 40);


}
void go_backward(){


  digitalWrite(direction_pin, HIGH);

  analogWrite(pwn_pin, 40);
}
void go_stop(){
  analogWrite(pwn_pin, 0);

  digitalWrite(direction_pin, LOW);

}

void loop()
{
  switch(input_command){
    case 1:
      go_forward();
      break;
    case 2:
      go_backward();
      break;
    case 3:
      go_stop();
      break;
  }

  if(to_publish){
    new_msg.data = input_command + (int8_t) 9;
    publish_data.publish(&new_msg);
    to_publish = false;
  }

  
  nh.spinOnce();
  delay(1);

}

