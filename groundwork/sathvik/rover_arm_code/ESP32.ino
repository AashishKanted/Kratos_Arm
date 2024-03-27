#include <ros.h>
#include <std_msgs/Int16.h>

ros::NodeHandle nh;

std_msgs::Int16 msg;
ros::Publisher pub("Orange_enc", &msg);

volatile unsigned int temp, counter = 0; 

void setup() {
  nh.initNode();
  nh.advertise(pub);
  // Serial.begin (115200);
  pinMode(27, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(27), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(5), ai1, RISING);
  }
  void loop() {
  if( counter != temp ){
    msg.data = counter;
    pub.publish(&msg);
    // Serial.println (counter);
  temp = counter;
  }
  nh.spinOnce();
  }
  void ai0() {
  if(digitalRead(5)==LOW) {
  counter++;
  }else{
  counter--;
  }
  }
  void ai1() {
  if(digitalRead(27)==LOW) {
  counter--;
  }else{
  counter++;
  }
  }
