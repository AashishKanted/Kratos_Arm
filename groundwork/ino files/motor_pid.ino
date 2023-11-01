#include <util/atomic.h> // For the ATOMIC_BLOCK macro
#include <ros.h>
#include <std_msgs/Int32.h>

#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE
#define PWM 8
#define DIRE 6
#define ENC_PULSE_REV 2353 //13 (pulses per rev) x 181 (gear ratio

volatile float theta = 0;

void inv_k(const std_msgs::Int32& msg){
  theta = msg.data;
}

ros:: NodeHandle nh;
std_msgs:: Int32 degree;
ros::Subscriber <std_msgs::Int32> sub("inv_k",&inv_k);

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  //Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  pinMode(PWM, OUTPUT);
  pinMode(DIRE, OUTPUT);

  //Serial.println("target pos");
}

void loop() {
  nh.spinOnce();
  // set target position
  int target = theta;
  //int target = 250*sin(prevT/1e6);

  // PID constants
  float kp = 1;
  float kd = 0.025;
  float ki = 0.0;

  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT)) / ( 1.0e6 );
  prevT = currT;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
  
//  // Calculate revolutions per minute
//  rpm4 = (float)(motor4_pulse_count * 60 / ENC_PULSE_REV);
//  rpm4 = abs(rpm4);
//  ang_velocity_4 = rpm4 * rpm_to_radians;
// ang_velocity_4_deg = ang_velocity_4 * rad_to_deg;

  // error
  int e = pos - target;

  // derivative
  float dedt = (e - eprev) / (deltaT);

  // integral
  eintegral = eintegral + e * deltaT;

  // control signal
  float u = kp * e + kd * dedt + ki * eintegral;

  // motor power
  float pwr = fabs(u);
  if ( pwr > 255 ) {
    pwr = 255;
  }

  // motor direction
  int dir = 1;
  if (u < 0) {
    dir = -1;
  }

  // signal the motor
  setMotor(dir, pwr, PWM, DIRE);


  // store previous error
  eprev = e;

//  Serial.print(target);
//  Serial.print(" ");
//  Serial.print(pos);
//  Serial.println();
}

void setMotor(int dir, int pwmVal, int pwm, int dire) {
  analogWrite(pwm, pwmVal);
  if (dir == -1) {
    digitalWrite(DIRE, HIGH);
  }
  else if (dir == 1) {
    digitalWrite(DIRE, LOW);
  }
  else {
    digitalWrite(DIRE, LOW);
  }
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  }
  else {
    posi--;
  }
}
