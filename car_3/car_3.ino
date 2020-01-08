#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

typedef struct {
  int button;   
  bool has;
} PACKAGE;

const byte address[6] = "23470";

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  pinMode(A7, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(A4, 0);
  digitalWrite(A5, 0);
}

int flick = 0;
void loop() {
  if(radio.available())
  {
    digitalWrite(4, flick);
    flick = ~flick;
    PACKAGE p;
    radio.read(&p, sizeof(p));
    Serial.print("Key");
    Serial.print(p.button);
    Serial.println();
    if(p.button == 10){
      digitalWrite(A4, 1);
    }
    else if(p.button == 7){
      digitalWrite(A4, 0);
    }
  }
}
