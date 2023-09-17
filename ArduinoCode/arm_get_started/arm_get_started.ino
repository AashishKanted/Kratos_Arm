

// 1 pe forward
// 2 pe backward
// 3 pe stop

int direction_pin = 6;
int pwn_pin = 9;

void setup() {
  Serial.begin(57600);

  pinMode(pwn_pin, OUTPUT);
  pinMode(direction_pin, OUTPUT);
  // put your setup code here, to run once:

}

void go_forward(){
  digitalWrite(direction_pin, LOW);

  analogWrite(pwn_pin, 40);


}
void go_backward(){


  digitalWrite(direction_pin, HIGH);

  analogWrite(pwn_pin, 40);
}
void go_stop(){
  analogWrite(pwn_pin, 0);

  digitalWrite(direction_pin, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

    if (Serial.available() > 0) {
    // read the incoming byte:
      int data = Serial.parseInt();
    
      Serial.print("I received: ");
      Serial.println(data);

      switch(data){
        case 1:
          go_forward();
          break;
        case 2:
          go_backward();
          break;
        case 3:
          go_stop();
          break;
      }
  }
  // else
  //   Serial.println("This wont print lite");


}
