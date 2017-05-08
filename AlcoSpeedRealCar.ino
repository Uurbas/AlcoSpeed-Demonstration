int Alcoholpin = A0;
int switchpin = 8;
uint8_t AlcoSpeed = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(switchpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  AlcoSpeed = (analogRead(Alcoholpin) >> 2);
  if (AlcoSpeed < 32)
  {
    digitalWrite(switchpin, HIGH);
    delay(100);
    digitalWrite(switchpin, LOW);
    delay(100);
  }
}
