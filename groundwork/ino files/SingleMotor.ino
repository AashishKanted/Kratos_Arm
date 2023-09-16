int Dir =  1;
int PWM =  2;

int input = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Dir, OUTPUT);
  pinMode(PWM, OUTPUT);

  digitalWrite(Dir, LOW);
  digitalWrite(Dir, LOW);
}

void loop() {
  while(Serial.available() == 0){

  }

  input = Serial.parseInt();

  if(input == 1){
    digitalWrite(PWM, HIGH);
    digitalWrite(Dir, LOW);
  }

  else if(input == 2){
    digitalWrite(PWM, HIGH);
    digitalWrite(Dir, HIGH);
  }

  else if(input == 3){
    digitalWrite(PWM, LOW);
    digitalWrite(Dir, LOW);
  }

  else{
  }
}
