//https://www.electroniclinic.com/arduino-dc-motor-speed-control-with-encoder-arduino-dc-motor-encoder/



#define Encoder_output_A 2  // pin2 of the Arduino
#define Encoder_output_B 3  // pin 3 of the Arduino

#define Motor_pin 5

// these two pins has the hardware interrupts as well.

unsigned int Count_pulses = 0;
unsigned int past_pulses = 0;
int count = 0;
int rpm = 0;
long last_millis = 0;
long current_millis = 0;

int initial_pulse_count = 0;
bool flag = 1;

void setup() {
  Serial.begin(9600);                // activates the serial communication
  pinMode(Encoder_output_A, INPUT);  // sets the Encoder_output_A pin as the input
  pinMode(Encoder_output_B, INPUT);  // sets the Encoder_output_B pin as the input
  pinMode(Motor_pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(Encoder_output_A), DC_Motor_Encoder, RISING);
  analogWrite(Motor_pin, 50);
  last_millis = millis();
}
long time = 0;

void loop() {
  // Serial.println("Result: ");
  // current_millis = millis();
  // Serial.println(Count_pulses);

  // code to exactly move 1/2 revolution
  if(Count_pulses - initial_pulse_count >= (13*52*4/1000)){
    analogWrite(Motor_pin, LOW);
  }

  
  time = millis() - last_millis;

  count = Count_pulses - past_pulses;
  float speed = count / (time/1000);
  speed = speed * 60 / (13*52*4);



  Serial.println(speed);

  
  past_pulses = Count_pulses;
  last_millis = millis();
  delay(1000);



  // Serial.println("RPM: ");
  // rpm = Count_pulses * 60 / 2400;
  // Serial.println(rpm);

}

void DC_Motor_Encoder() {
  int b = digitalRead(Encoder_output_B);
  if (b > 0) {
    Count_pulses++;
  } else {
    Count_pulses--;
  }

  if(flag)
  {
    initial_pulse_count = Count_pulses;
    flag = 0;
  }
}