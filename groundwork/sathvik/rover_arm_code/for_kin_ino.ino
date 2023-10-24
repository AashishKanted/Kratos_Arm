#include <ros.h>
#include <Servo.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

geometry_msgs::Twist params;
ros::Publisher pub("parameters", &params);

Servo servo_1;
Servo servo_2;

// extra soldered wires of servo
const int servoAnalogOut1 = A3;
const int servoAnalogOut2 = A4;

void setup() {
  nh.initNode();
  nh.advertise(pub);
}

void loop() {
  params.angular.x = map(analogRead(servoAnalogOut1),127,489, 0, 180);
  params.angular.y = map(analogRead(servoAnalogOut2),127,489, 0, 180);

  pub.publish(&params);
  nh.spinOnce();
  delay(400);
}
