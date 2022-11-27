// Motor encoder output pulses per 360 degree revolution (measured manually)
#define ENC_COUNT_REV 2353
 
// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 2
 
// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC_IN_RIGHT_B 3
#define PWM 4
#define DIRE 5

#include <ros.h>
#include <std_msgs/Float32.h>
std_msgs::Float32 encoder_msg;
//std_msgs::Float32 pid_msg;
ros::Publisher pub_encoder("encoder", &encoder_msg);
ros::NodeHandle nh;
void msgcall(const std_msgs::Float32& pid_msg){
  int dir =1;
  float pwr;
  if(pid_msg.data <0)  
  {
    dir = -1;
    pwr = -1*fabs(pid_msg.data);
   }
   else
   {
     pwr = fabs(pid_msg.data); 
    }
   
    
  setMotor(dir, pwr, PWM, DIRE);

    
   }
 void setMotor(int dir, int pwmVal, int pwm, int dire) {
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(DIRE, HIGH);
  }
  else if (dir == -1) {
    digitalWrite(DIRE, LOW);
  }
  else {
    digitalWrite(DIRE, LOW);
  }
 }
ros::Subscriber<std_msgs::Float32> sub("pid_out", &msgcall );
//float msg.data = &pid_msg
// True = Forward; False = Reverse
boolean Direction_right = true;
// 
// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;
 
// One-second interval for measurements
int interval = 1000;
  
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
float rpm_right = 0;
  //right_wheel_pulse;
 
// Variable for angular velocity measurement
float ang_velocity_right = 0;
float ang_velocity_right_deg = 0;
 
const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;

void right_wheel_pulse() {
   
  // Read the value for the encoder for the right wheel
  int val = digitalRead(ENC_IN_RIGHT_B);
 
  if(val == LOW) {
    Direction_right = false; // Reverse
  }
  else {
    Direction_right = true; // Forward
  }
   
  if (Direction_right) {
    right_wheel_pulse_count++;
  }
  else {
    right_wheel_pulse_count--;
  }
}


void setup() {
 
  // Open the serial port at 9600 bps
  Serial.begin(9600); 
  nh.initNode();
  nh.advertise(pub_encoder);
  nh.subscribe(sub);
 
   // Set pin states of the encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B , INPUT);
  pinMode(PWM,OUTPUT);
  pinMode(DIRE,OUTPUT);
 
  // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
   
}
 
void loop() {
 
  // Record the time
  currentMillis = millis();
 
  // If one second has passed, print the number of pulses
  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
 
    // Calculate revolutions per minute
    rpm_right = (float)(right_wheel_pulse_count * 60 / ENC_COUNT_REV);
    ang_velocity_right = rpm_right * rpm_to_radians;   
    ang_velocity_right_deg = ang_velocity_right * rad_to_deg;
     //Serial.print(" Pulses: ");
    //Serial.println(right_wheel_pulse_count);
    //Serial.print(" Speed: ");
    //Serial.print(rpm_right);
    //Serial.println(" RPM");
    //Serial.print(" Angular Velocity: ");
    //Serial.print(rpm_right);
    //Serial.print(" rad per second");
    //Serial.print("\t");
    //Serial.print(ang_velocity_right_deg);
    //Serial.println(" deg per second");
    //Serial.println();
 
    right_wheel_pulse_count = 0;

    // Increment the number of pulses by 1

   encoder_msg.data = ang_velocity_right_deg;
   pub_encoder.publish(&encoder_msg);
  }

  nh.spinOnce();
}
