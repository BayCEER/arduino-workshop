#include <BayTCPSim900.h>

#define GPRS_BAUD 9600
#define GPRS_POWER_PIN 7
BayGPRS client=BayGPRS(Serial);


void setup() {
  blink(1);
  
  pinMode(GPRS_POWER_PIN,OUTPUT);
  digitalWrite(GPRS_POWER_PIN,HIGH);
  //TODO: CHANGE CONFIG!!
  client.readConfigFromStringPGM(PSTR("132.180.112.128|80|gateway/frame/saveFlat|import|import|SIM800L-SPI|pinternet.interkom.de|||4814|"));
  client.begin(GPRS_BAUD);
  //TODO: Change phone number and text!
  client.sendSMS("+4915150290345","SMS von Arduino ;-)");

  blink(3);
  
  digitalWrite(GPRS_POWER_PIN,LOW);
  
  
}

void loop() {
}


void blink(uint8_t times){
  pinMode(LED_BUILTIN,OUTPUT);
  while(times){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
    times--;
  }
  pinMode(LED_BUILTIN,INPUT);
}

