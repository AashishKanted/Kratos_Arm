/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
// #include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>

#include <std_msgs/Int16.h>

// #include <std_msgs/String.h>


int l_direction_pin = 8;
int l_pwn_pin = 9;


int r_direction_pin = 12;
int r_pwn_pin = 11;

int act1_direction_pin = 7;
int act1_pwn_pin = 3;


int act2_direction_pin = 4;
int act2_pwn_pin = 5;



ros::NodeHandle nh;

std_msgs::Int8 new_msg;

ros::Publisher publish_data("/modified_data", &new_msg);

int8_t input_command;

int16_t act_1_val;
int16_t act_2_val;
bool to_publish = false;

void messageCb(const std_msgs::Int8& toggle_msg) {

  input_command = toggle_msg.data;
  to_publish = true;


  digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN));  // blink the led
}

void messageCb_act1(const std_msgs::Int16& toggle_msg) {

  act_1_val = toggle_msg.data;
  // act_1_val -=255;
  // to_publish = true;


  // digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN));  // blink the led
}

void messageCb_act2(const std_msgs::Int16& toggle_msg) {

  act_2_val = toggle_msg.data;
  // act_2_val -=255;
  // to_publish = true;


  // digitalWrite(LED_BUILTIN, HIGH - digitalRead(LED_BUILTIN));  // blink the led
}


ros::Subscriber<std_msgs::Int8> sub1("/control_motors", &messageCb);

ros::Subscriber<std_msgs::Int16> sub2("/control_motors_act1", &messageCb_act1);
ros::Subscriber<std_msgs::Int16> sub3("/control_motors_act2", &messageCb_act2);


void setup() {
  digitalWrite(act1_direction_pin, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  
  nh.initNode();

  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(sub3);

  nh.advertise(publish_data);



  pinMode(l_pwn_pin, OUTPUT);
  pinMode(l_direction_pin, OUTPUT);

  pinMode(r_pwn_pin, OUTPUT);
  pinMode(r_direction_pin, OUTPUT);

  pinMode(act1_pwn_pin, OUTPUT);
  pinMode(act1_direction_pin, OUTPUT);

  pinMode(act2_pwn_pin, OUTPUT);
  pinMode(act2_direction_pin, OUTPUT);
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

void move_motor(int motor_id, int val, int dir){
  if(motor_id == 1){
    if(dir == 1)
      digitalWrite(act1_direction_pin, HIGH);
    if(dir == 0)
      digitalWrite(act1_direction_pin, LOW);
    analogWrite(act1_pwn_pin, val);
  }
  if(motor_id == 2){
    if(dir == 1)
      digitalWrite(act2_direction_pin, HIGH);
    if(dir == 0)
      digitalWrite(act2_direction_pin, LOW);
    // digitalWrite(act2_direction_pin, dir);
    analogWrite(act2_pwn_pin, val);

  }
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

  if(act_1_val >= 0)
    move_motor(1, act_1_val, 0);
  else if(act_1_val < 0)
    move_motor(1, ((-1) * act_1_val), 1);
  
  if(act_2_val >= 0)
    move_motor(2, act_2_val, 0);
  else if(act_2_val < 0)
    move_motor(2, ((-1) * act_2_val), 1);
  

  // if(act_1_val >= 0){
  //   digitalWrite(act1_direction_pin, LOW);
  //   analogWrite(act1_pwn_pin, act_1_val);
  // }

  // if(act_1_val < 0){
  //       digitalWrite(act1_direction_pin, HIGH);
  //   analogWrite(act1_pwn_pin, -1 * act_1_val);

  // }
  // FOR FUTURE FEEDBACK

  if (to_publish) {
    new_msg.data = input_command + (int8_t) (-1);
    publish_data.publish(&new_msg);
    to_publish = false;
  }


  nh.spinOnce();
  delay(1);
}
