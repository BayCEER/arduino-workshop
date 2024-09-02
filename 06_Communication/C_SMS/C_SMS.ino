#include <BayTCPSim900.h>

#define GPRS_BAUD 9600
#define GPRS_POWER_PIN 7
BayGPRS client=BayGPRS(Serial);


void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN,LOW);
  pinMode(GPRS_POWER_PIN,OUTPUT);
  digitalWrite(GPRS_POWER_PIN,HIGH);
  //TODO: CHANGE CONFIG!!
  client.readConfigFromStringPGM(PSTR("132.180.112.128|80|gateway/frame/saveFlat|import@Workshop|import|SIM800L-SPI|iot.1nce.net||||"));
  client.begin(GPRS_BAUD);
  //TODO: Change phone number and text!
  uint8_t res=client.sendSMS("+4915150290345","SMS von Arduino ;-)");

  for(int8_t i=0;i<(res+1);i++){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
  }
  digitalWrite(GPRS_POWER_PIN,LOW);
  
  
}

void loop() {
}
