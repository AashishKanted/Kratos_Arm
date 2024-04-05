#include <ros.h>
#include <std_msgs/Int16.h>

ros::NodeHandle nh;

std_msgs::Int16 msg1;
ros::Publisher pub1("Orange_enc_1", &msg1);

std_msgs::Int16 msg2;
ros::Publisher pub2("Orange_enc_2", &msg2);

int temp1, counter1 = 0;
int temp2, counter2 = 0;

void setup() {
  nh.initNode();
  nh.advertise(pub1);
  nh.advertise(pub2);
  // Serial.begin (115200);
  pinMode(27, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(27), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(5), ai1, RISING);

  pinMode(25, INPUT_PULLUP); 
  pinMode(32, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(25), ai2, RISING);
  attachInterrupt(digitalPinToInterrupt(32), ai3, RISING);
  }

void loop() {
  // if( counter1 != temp1 ){
  //   msg1.data = counter1;
  //   pub1.publish(&msg1);
  //   // Serial.println (counter1);
  //   temp1 = counter1;
  // }

  // if( counter2 != temp2 ){
  //   msg2.data = counter2;
  //   pub2.publish(&msg2);
  //   // Serial.println (counter2);
  //   temp2 = counter2;
  // }

  msg1.data = counter1;
  pub1.publish(&msg1);

  msg2.data = counter2;
  pub2.publish(&msg2);

  delay(10);
  nh.spinOnce();
  }
void ai0() {
  if(digitalRead(5)==LOW) {
  counter1++;
  }else{
  counter1--;
  }
}
void ai1() {
  if(digitalRead(27)==LOW) {
  counter1--;
  }else{
  counter1++;
  }
}
void ai2() {
  if(digitalRead(32)==LOW) {
  counter2++;
  }else{
  counter2--;
  }
}
void ai3() {
  if(digitalRead(25)==LOW) {
  counter2--;
  }else{
  counter2++;
  }
}
