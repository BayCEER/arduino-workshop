#include <Sleep.h>

void schalter(void){
  Serial.println("INT0");
}

ISR(TIMER2_OVF_vect){
  digitalWrite(5, ! digitalRead(5));
}

ISR(WDT_vect) {
  Serial.println("WDT");  
}

const byte interruptPin = 2;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Starting...");
  Sleep.setupTimer2(); //init timer2 to 1 sec
  Sleep.setupWatchdog(); //init watchdog timer to about 1 sec
  attachInterrupt(digitalPinToInterrupt(interruptPin), schalter, FALLING);
}


void loop() {

}
