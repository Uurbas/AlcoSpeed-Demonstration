#include <SPI.h>
#include "RF24.h"
int msg[2];
//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8
RF24 radio(8, 7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int potpin1 = A0;
int potpin2 = A1;
int val1;
int val2;

int Alcoholpin = A2;
uint8_t AlcoSpeed;

void setup(void) {
  //Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  AlcoSpeed=0;
}
void loop(void) {
  AlcoSpeed = (analogRead(Alcoholpin)>>2);
  //Serial.print(AlcoSpeed);
  //Serial.print(",");
  delay(2);
  if (AlcoSpeed<32)
  {
    val1 = analogRead(potpin1);
    val1 = map(val1, 0, 1023, 0, 40);
    val2 = analogRead(potpin2);
    val2 = map(val2, 0, 1023, 0, 40);
    delay(1);
    msg[0] = val1;
    msg[1] = val2;
    radio.write(msg, sizeof(msg));
    //Serial.print(val1);
    //Serial.print(",");
    //Serial.println(val2);

  }
  else
  {
    msg[0] = 20;
    msg[1] = 20;
    radio.write(msg, sizeof(msg));
  }

}
