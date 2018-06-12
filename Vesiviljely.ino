#include <Ticker.h>

uint8_t lightRelayPin = D0;
uint8_t pumpRelayPin = D1;
uint16_t lightOnTime = 16*60; //16h h*min
uint16_t lightOffTime = 8*60;
uint16_t pumpOnTime = 4; // 4min
uint16_t pumpOffTime = (8*60)-pumpOnTime; // 7h 56min

uint16_t lightOnCounter = 0;
uint16_t lightOffCounter = 0;
uint16_t pumpOnCounter = 0;
uint16_t pumpOffCounter = 0;

uint8_t pumpStatus=0;
uint8_t lightStatus=0;

Ticker minuteTick;

void MinuteTick() {
  if( lightStatus ) lightOnCounter++;    
  else lightOffCounter++;
  if( pumpStatus ) pumpOnCounter++;
  else pumpOffCounter++;
  
  if( lightOnTime <= lightOnCounter ) {
    lightOnCounter=0;
    lightOff();
  }
  if( lightOffTime <= lightOffCounter ) {
    lightOffCounter=0;
    lightOn();
  }
  if( pumpOnTime <= pumpOnCounter ) {
    pumpOnCounter=0;
    pumpOff();
  }
  if( pumpOffTime <= pumpOffCounter ) {
    pumpOffCounter=0;
    pumpOn();
  }
}

void pumpOff() {
  Serial.println("Stop watter pump");
  digitalWrite(pumpRelayPin, HIGH);
  pumpStatus=0;
}

void pumpOn() {
  Serial.println("Start watter pump");
  digitalWrite(pumpRelayPin, LOW);
  pumpStatus=1;
}

void lightOff() {
  Serial.println("Turn light off");
  digitalWrite(lightRelayPin, HIGH);
  lightStatus=0;
}

void lightOn() {
  Serial.println("Turn light on");
  digitalWrite(lightRelayPin, LOW);
  lightStatus=1;
}

void setup() {
  Serial.begin(115200);
  pinMode(lightRelayPin, OUTPUT);
  pinMode(pumpRelayPin, OUTPUT);
  Serial.println("Started water pump and light control");
  minuteTick.attach(60, MinuteTick);
  pumpOn();
  lightOn();
}

void loop() {
  // put your main code here, to run repeatedly:

}
