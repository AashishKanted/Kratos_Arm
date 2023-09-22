


#include <ros.h>
// #include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>


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



ros::Subscriber<std_msgs::Int8> sub1("/control_stepper", &messageCb);



// Define stepper motor connections:
#define dirPin 5
#define stepPin 6

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  nh.initNode();

  nh.subscribe(sub1);


  // Set the spinning direction CW/CCW:
  digitalWrite(dirPin, HIGH);
}

void loop() {

  switch (input_command) {
    case 10:
      //forward
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
      digitalWrite(dirPin, HIGH);


      break;
    case 5:
      //backward

      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);

      digitalWrite(dirPin, LOW);

      break;
  }

  nh.spinOnce();
  delay(1);
}
