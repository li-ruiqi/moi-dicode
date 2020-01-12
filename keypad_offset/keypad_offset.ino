#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const byte address[6] = "23470";
RF24 radio(10, 9); // CE, CSN

typedef struct {
  int button;
  bool has;
} PACKAGE;

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

int prev = 0;
unsigned long ptime = 0;

int myabs(int x, int y)
{
  if(x>y)
    return x-y;
  return y-x;
}

void loop() {
  
  int key = 0;
  int val = analogRead(A0);
  delay(51);
  int prevval = analogRead(A0);
  if(myabs(val,prevval) <= 8)
  {
  
  PACKAGE p;
  
  if(val >= 977)
    key = 1;
  else if(val >= 893)
    key = 2;
  else if(val >= 822)
    key = 3;
  else if(val >= 761)
    key = 4;
  else if(val >= 708)
    key = 5;
  else if(val >= 662)
    key = 6;
  else if(val >= 620)
    key = 7;
  else if(val >= 585)
    key = 8;
  else if(val >= 554)
    key = 9;
  else if(val >= 525) 
    key = 10;
  else if(val >= 500) 
    key = 11;
  else if(val >= 450) 
    key = 12;
  
  if(prev != key)
  {
    prev = key;
    if(key == 0)
      Serial.print("OFF");
    else
    {
      Serial.print("Button ");
      Serial.print(key);
      Serial.print(val);  
      p.button = key + 100;
      p.has = true;
      radio.write(&p, sizeof(p));
      ptime = millis();
    }
    Serial.println();
  }
  if(millis() - ptime > 500)
  { 
    ptime = millis();
    p.button = 0;
    p.has = false;
    radio.write(&p, sizeof(p));
  }
  }
  prevval = val;
}
