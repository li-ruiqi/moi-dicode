#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define SERVO_1_START 141
#define SERVO_2_START 34
#define SERVO_3_START 175
#define SERVO_4_START 0
#define SERVO_5_START 179

#define SERVO_1_END 53
#define SERVO_2_END 124
#define SERVO_3_END 0
#define SERVO_4_END 175
#define SERVO_5_END 4

Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;

RF24 radio(9, 10); // CE, CSN

typedef struct {
  int button;
  bool has;
} PACKAGE;

const byte address[6] = "23470";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2,1);

  /*BOTTOM*/
  servo_1.attach(3, 500, 2500);
  servo_1.write(SERVO_1_START);

  delay(500);

  servo_2.attach(4, 500, 2500);
  servo_2.write(SERVO_2_START);

  /*MIDDLE*/

  servo_3.attach(5, 500, 2500);
  servo_3.write(SERVO_3_START);

  delay(500);

  servo_4.attach(6, 500, 2500);
  servo_4.write(SERVO_4_START);

  /*TOP*/

  servo_5.attach(7, 500, 2500);
  servo_5.write(SERVO_5_START);

  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

}

int flick = 0;
void loop() {
  if(radio.available())
  {
    digitalWrite(2, flick);
    flick = ~flick;
    PACKAGE p;
    radio.read(&p, sizeof(p));
    Serial.print("Key");
    Serial.print(p.button);
    Serial.println();

    if(p.button == 3){
      servo_1.write(SERVO_1_END);
      delay(500);
      servo_2.write(SERVO_2_END);
      servo_3.write(SERVO_3_END);
      delay(500);
      servo_4.write(SERVO_4_END);
      servo_5.write(SERVO_5_END);
    }
    else if(p.button == 6){
      servo_1.write(SERVO_1_START);
      delay(500);
      servo_2.write(SERVO_2_START);
      servo_3.write(SERVO_3_START);
      delay(500);
      servo_4.write(SERVO_4_START);
      servo_5.write(SERVO_5_START);
    }
  }
}
