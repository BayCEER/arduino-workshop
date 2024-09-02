#include <BayRF24.h>

//TODO: CHANGE ADDRESS 
#define RF24ADDRESS 0x45c431ae12LL
//#define RF24ADDRESS 0x45c431ae24LL
//#define RF24ADDRESS 0x45c431ae48LL
//#define RF24ADDRESS 0x45c431ae96LL
//#define RF24ADDRESS 0x45c431aeabLL
//#define RF24ADDRESS 0x45c431aebfLL

#define RF24CHANNEL 0x6e

BayRF24 client=BayRF24(9,10);

void setup(void){
  //RF24 geht über SPI
  //Am gleichen Bus hängt auch der Flash Speicher
  //Mit den folgenden zwei Zeilen wird dieser sicher deaktiviert.
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  client.init(RF24ADDRESS,RF24CHANNEL);
}

void loop(void){
   // Construct DataFrame
   client.startDataFrame(BayEOS_Float32le,1);
   client.addChannelValue(millis()/1000); //CPU-Time in sec
   client.addChecksum(); 
   if(client.sendPayload())
     blink(2);
   else
     blink(1);   
   
    
  delay(5000);
   
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
}
