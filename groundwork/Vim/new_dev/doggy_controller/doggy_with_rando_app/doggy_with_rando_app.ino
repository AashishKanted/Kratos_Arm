#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

#include <Cytron_SmartDriveDuo.h>

int speed = 30;

#define IN1 9
#define BAUDRATE 115200
Cytron_SmartDriveDuo smartDriveDuo30(SERIAL_SIMPLIFIED, IN1, BAUDRATE);
 float right_wheel=0;
 float left_wheel=0;
 float linear=0;
 float angular=0;



void setup() {
  Serial.begin(9600);  // Set the baud rate for serial communication
  // Initialize any other necessary setup code here
}
void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    executeCommand(command);
  }
  // Continue with other tasks in your main loop
}
void executeCommand(char command) {
    if(speed > 100)
      speed = 100;
    if(speed < 10)
      speed = 10;
  switch (command) {
    case FORWARD:
      right_wheel = speed;
      left_wheel = speed;
      // Perform action for moving forward
      break;
    case BACKWARD:
      right_wheel = -speed;
      left_wheel = -speed;
      // Perform action for moving backward
      break;
    case LEFT:
      right_wheel = -speed; //JUGAD
      left_wheel = speed;
      // Perform action for turning left
      break;
    case RIGHT:
    right_wheel = speed;
      left_wheel = -speed;
      // Perform action for turning right
      break;
    case CIRCLE:
      // Perform action for circle
      break;
    case CROSS:
      speed -= 10;
      // Perform action for immediate stop or crossing
      break;
    case TRIANGLE:
      speed += 10;
      // Perform action for toggling a state (e.g., LED on/off)
      break;
    case SQUARE:
      // Perform action for retrieving and sending status information
      break;
    case START:
      
      // Perform action for starting a process or operation
      break;
    case PAUSE:
      // Perform action for pausing a process or operation
      right_wheel = 0;
      left_wheel = 0;
      break;
    default:
      // Invalid command received
      break;
  }

  smartDriveDuo30.control(right_wheel,left_wheel);
}