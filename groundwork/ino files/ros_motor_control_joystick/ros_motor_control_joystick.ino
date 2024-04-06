/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
// #include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>
// #include <std_msgs/String.h>


int l_direction_pin = 6;
int l_pwn_pin = 9;


int r_direction_pin = 8;
int r_pwn_pin = 10;


ros::NodeHandle nh;

std_msgs::Int8 new_msg;

ros::Publisher publish_data("/modified_data", &new_msg);

int8_t input_command;
bool to_publish = false;

void messageCb(const std_msgs::Int8& toggle_msg) {

  input_command = toggle_msg.data;
  to_publish = true;


  digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN));  // blink the led
}

ros::Subscriber<std_msgs::Int8> sub("/control_motor", &messageCb);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(publish_data);



  pinMode(l_pwn_pin, OUTPUT);
  pinMode(l_direction_pin, OUTPUT);

  pinMode(r_pwn_pin, OUTPUT);
  pinMode(r_direction_pin, OUTPUT);
}



void both_go_forward() {
  digitalWrite(l_direction_pin, LOW);
  analogWrite(l_pwn_pin, 40);

  digitalWrite(r_direction_pin, LOW);
  analogWrite(r_pwn_pin, 40);
}

void both_go_backward() {
  digitalWrite(l_direction_pin, HIGH);
  analogWrite(l_pwn_pin, 40);

  digitalWrite(r_direction_pin, HIGH);
  analogWrite(r_pwn_pin, 40);
}


void left_f() {
  digitalWrite(l_direction_pin, LOW);
  analogWrite(l_pwn_pin, 40);

  digitalWrite(r_direction_pin, HIGH);
  analogWrite(r_pwn_pin, 40);
}


void right_f() {
  digitalWrite(l_direction_pin, HIGH);
  analogWrite(l_pwn_pin, 40);

  digitalWrite(r_direction_pin, LOW);
  analogWrite(r_pwn_pin, 40);
}


void both_stop() {
  digitalWrite(l_direction_pin, LOW);
  analogWrite(l_pwn_pin, 0);

  digitalWrite(r_direction_pin, LOW);
  analogWrite(r_pwn_pin, 0);
}

void loop() {
  switch (input_command) {
    case 2:
      both_go_forward();
      break;
    case 4:
      both_go_backward();
      break;
    case 8:
      left_f();
      break;
    case 16:
      right_f();
      break;
    case 32:
      both_stop();
      break;
    
  }



  // FOR FUTURE FEEDBACK

  if (to_publish) {
    new_msg.data = input_command + (int8_t) (-1);
    publish_data.publish(&new_msg);
    to_publish = false;
  }


  nh.spinOnce();
  delay(1);
}
