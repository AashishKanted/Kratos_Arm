
int DirPin = 4;
int PWM = 2;
int input = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DirPin,OUTPUT);
  pinMode(PWM,OUTPUT);
  
  digitalWrite(DirPin,LOW);
  digitalWrite(PWM,LOW);
}

void loop() {
  while(Serial.available() == 0){
  }
  
  input = Serial.parseInt();
  if(input == 1){
    digitalWrite(PWM,HIGH);
    digitalWrite(DirPin,LOW);
  }
  else if(input == 2){
    digitalWrite(PWM,HIGH);
    digitalWrite(DirPin,HIGH);
  }
  else if(input == 3){
    digitalWrite(PWM,LOW);
    digitalWrite(PWM,LOW);
  }
  else{
    
  }
}
