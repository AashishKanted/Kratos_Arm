#include <ros.h>
#include <std_msgs/Float32.h>
#define ENC_PULSE_REV 2353 //13 (pulses per rev) x 181 (gear ratio

#define ENC4_A 2





 ros:: NodeHandle nh;
 
void volt( const std_msgs::Float32){
  analogWrite(A0,&volt);
  }

 std_msgs:: Float32 degree;
 ros::Subscriber <std_msgs::Float32> sub("pid_out",&volt);
 ros::Publisher pub("encoder",&degree);

// Other encoder output to Arduino to keep track of wheel direction
// Tracks the direction of rotation.
#define ENC4_B 4
 
// Keep track of the number of 4 wheel pulses
volatile long motor4_pulse_count = 0;
 
// One-second interval for measurements
int interval = 1000; //pulses for this interval is displayed
  
// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;
 
// Variable for RPM measuerment
float rpm4 = 0;
 
// Variable for angular velocity measurement
float ang_velocity_4 = 0;
float ang_velocity_4_deg = 0;
 
const float rpm_to_radians = 0.10471975512;
const float rad_to_deg = 57.29578;
 
void setup() {
 
  // Open the serial port at 9600 bps
  Serial.begin(9600); 
 
  // Set pin states of the encoder
  pinMode(ENC4_A , INPUT_PULLUP);
  pinMode(ENC4_B , INPUT);
  // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC4_A), motor4_pulse, RISING);
   
}
 
void loop() {
 
  // Record the time
  currentMillis = millis();
 
  // If one second has passed, print the number of pulses
  if (currentMillis - previousMillis > interval) {
 
    previousMillis = currentMillis;
    // Calculate revolutions per minute
    rpm4 = (float)(motor4_pulse_count * 60 / ENC_PULSE_REV);
    rpm4 = abs(rpm4);
    ang_velocity_4 = rpm4 * rpm_to_radians;   
    ang_velocity_4_deg = ang_velocity_4 * rad_to_deg;
    
     
    Serial.print(" Pulses: ");
    Serial.println(motor4_pulse_count);
    Serial.print(" Speed: ");
    Serial.print(rpm4);
    Serial.println(" RPM");
    Serial.print(" Angular Velocity: ");
    Serial.print(rpm4);
    Serial.print(" rad per second");
    Serial.print("\t");
    Serial.print(ang_velocity_4_deg);
    Serial.println(" deg per second");
    
 
    motor4_pulse_count = 0;
   
  degree.data= ang_velocity_4_deg*currentMillis*1000;
  pub.publish(&degree);
  
  
  }
}
 
// Increment the number of pulses by 1
void motor4_pulse() {
   
  // Read the value for the encoder for the 4 wheel
  int val = digitalRead(ENC4_B);
 
  if(val == LOW) {
     motor4_pulse_count--;
  }
  else {
    motor4_pulse_count++;
  }
   
 
}
