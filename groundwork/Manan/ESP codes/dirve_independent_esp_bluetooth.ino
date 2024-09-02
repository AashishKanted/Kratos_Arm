#include <BluetoothSerial.h>
#include <Cytron_SmartDriveDuo.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to enable it.
#endif

BluetoothSerial SerialBT;

// Motor control setup for 6 wheels
#define IN1 5
#define IN2 18
#define IN3 19
#define BAUDRATE 115200

Cytron_SmartDriveDuo smartDriveDuo30_1(SERIAL_SIMPLIFIED, IN1, BAUDRATE);
Cytron_SmartDriveDuo smartDriveDuo30_2(SERIAL_SIMPLIFIED, IN2, BAUDRATE);
Cytron_SmartDriveDuo smartDriveDuo30_3(SERIAL_SIMPLIFIED, IN3, BAUDRATE);

// Movement and speed variables
int speed = 30;
float right_wheel_front = 0;
float left_wheel_front = 0;
float right_wheel_middle = 0;
float left_wheel_middle = 0;
float right_wheel_back = 0;
float left_wheel_back = 0;

// Command definitions
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

void setup() {
  Serial.begin(115200);  // Start serial communication for debugging
  SerialBT.begin("Kratos_ESP32");  // Bluetooth device name
  Serial.println("Bluetooth device started, now you can pair it with your smartphone!");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    executeCommand(command);
  }
  delay(100);
}

void executeCommand(char command) {
  if (speed > 100) speed = 100;
  if (speed < 10) speed = 10;

  switch (command) {
    case FORWARD:
      right_wheel_front = left_wheel_front = speed;
      right_wheel_middle = left_wheel_middle = speed;
      right_wheel_back = left_wheel_back = speed;
      Serial.println("F");
      break;
    case BACKWARD:
      right_wheel_front = left_wheel_front = -speed;
      right_wheel_middle = left_wheel_middle = -speed;
      right_wheel_back = left_wheel_back = -speed;
      Serial.println("B");
      break;
    case LEFT:
      right_wheel_front = -speed*1.488;
      right_wheel_middle = -speed;
      right_wheel_back = -speed*1.33;
      left_wheel_front = speed*1.488;
      left_wheel_middle = speed;
      left_wheel_back = speed*1.33;
      Serial.println("L");
      break;
    case RIGHT:
      right_wheel_front = speed*1.488;
      right_wheel_middle = speed;
      right_wheel_back = speed*1.33;
      left_wheel_front = -speed*1.488;
      left_wheel_middle = -speed;
      left_wheel_back = -speed*1.33;
      Serial.println("R");
      break;
    case CIRCLE:
      // Perform action for circle
      break;
    case CROSS:
      speed -= 10;
      break;
    case TRIANGLE:
      speed += 10;
      break;
    case SQUARE:
      // Perform action for retrieving and sending status information
      break;
    case START:
      // Perform action for starting a process or operation
      break;
    case PAUSE:
      right_wheel_front = left_wheel_front = 0;
      right_wheel_middle = left_wheel_middle = 0;
      right_wheel_back = left_wheel_back = 0;
      break;
    default:
      Serial.println("Invalid command received!");
      break;
  }

  smartDriveDuo30_1.control(right_wheel_front, left_wheel_front);
  smartDriveDuo30_2.control(right_wheel_middle, left_wheel_middle);
  smartDriveDuo30_3.control(right_wheel_back, left_wheel_back);
}