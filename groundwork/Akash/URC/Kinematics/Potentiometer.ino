#include <ros.h>
#include <geometry_msgs/Point.h>

ros::NodeHandle nh;

geometry_msgs::Point potentiometer;
ros::Publisher pub("Potentiometer_values",&potentiometer);

const int pot_1 = A0;
const int pot_2 = A1;

void setup() {
  nh.initNode();
  nh.advertise(pub);
}

void loop() {
  potentiometer.x = analogRead(pot_1);
  potentiometer.y = analogRead(pot_2);

  pub.publish(&potentiometer);
  nh.spinOnce();

  pub.publish(&potentiometer);

}
