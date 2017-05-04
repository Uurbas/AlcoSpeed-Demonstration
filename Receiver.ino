#include <SPI.h>
#include "RF24.h"
//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8
RF24 radio(8, 7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int msg[2];
int in1 = A0;
int in2 = A1;
int in3 = A2;
int in4 = A3;
int enA = 3;
int enB = 5;
void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
void loop()
{
  if (radio.available()) {
    radio.read(msg, sizeof(msg));
    //
    if (0 <= msg[0] && msg[0] <= 18)//forward part
    {
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
      delay(40 - msg[0]);
      digitalWrite(enA, LOW);
      digitalWrite(enB, LOW);
      delay(msg[0]);
      digitalWrite(in1, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in4, LOW);

      if (msg[1] <= 40 && 22 <= msg[1])//turn right
      {
        digitalWrite(enA, HIGH);
        //digitalWrite(enB, HIGH);
        delay(msg[1]);
        digitalWrite(enA, LOW);
        digitalWrite(enB, LOW);
        delay(40 - msg[1]);
        digitalWrite(in1, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in4, LOW);
      }
      if (0 <= msg[1] && msg[1] <= 18)//turn left
      {
        //digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
        delay(40 - msg[1]);
        digitalWrite(enA, LOW);
        digitalWrite(enB, LOW);
        delay(msg[1]);
        digitalWrite(in1, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in4, LOW);
      }
    }
    if (msg[0] <= 40 && 22 <= msg[0])//backward part
    {
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
      delay(msg[0]);
      digitalWrite(enA, LOW);
      digitalWrite(enB, LOW);
      delay(40 - msg[0]);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, HIGH);
      digitalWrite(in1, LOW);
      digitalWrite(in3, LOW);
      if (msg[1] <= 40 && 22 <= msg[1])//turn right
      {
        digitalWrite(enA, HIGH);
        //digitalWrite(enB, HIGH);
        delay(msg[1]);
        digitalWrite(enA, LOW);
        digitalWrite(enB, LOW);
        delay(40 - msg[1]);
        digitalWrite(in2, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in1, LOW);
        digitalWrite(in3, LOW);
      }
      if (0 <= msg[1] && msg[1] <= 18)//turn left
      {
        //digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
        delay(40 - msg[1]);
        digitalWrite(enA, LOW);
        digitalWrite(enB, LOW);
        delay(msg[1]);
        digitalWrite(in2, HIGH);
        digitalWrite(in4, HIGH);
        digitalWrite(in1, LOW);
        digitalWrite(in3, LOW);
      }
    }
    //    Serial.print("msg0 : ");
    //    Serial.println(msg[0]);
    //    Serial.print("msg1 : ");
    //    Serial.println(msg[1]);
    //delay(100);
  }
}
