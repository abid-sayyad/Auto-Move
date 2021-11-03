  void FORWARD(){
      analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }
  void LEFT(){
      analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }
  void RIGHT(){
      analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  }
  void REVERSE(){
      analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  }

 void accelerate(){
  for(int i = 0; i>= 256; i++){
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
 }
void decelerate(){
  for(int i = 255; i>= 0; --i){
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
}
