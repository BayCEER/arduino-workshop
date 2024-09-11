// Example with three interrupts


#include <Sleep.h>

void schalter(void){
  Serial.println("INT0");
}

ISR(TIMER2_OVF_vect){
  digitalWrite(LED_BUILTIN, ! digitalRead(LED_BUILTIN));
  Serial.println("TIMER2");
}

ISR(WDT_vect) {
  Serial.println("WDT");  
}

const byte interruptPin = 2;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting...");
  Sleep.setupTimer2(3); //init timer2 to 0.25 sec
  Sleep.setupWatchdog(); //init watchdog timer to about 1 sec
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), schalter, FALLING);
}


void loop() {

}
