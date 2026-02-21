void setup(){
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  analogWrite(11, 200);
  delay(1500);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(100);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  analogWrite(11, 0);
}

void loop(){}