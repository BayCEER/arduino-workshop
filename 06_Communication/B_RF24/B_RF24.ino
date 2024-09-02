#include <RF24.h>
RF24 radio(9,10);

// TODO 
// - Open the IDE library manager and install the RF24 by TMRh20 library
// - Define a channel
// - Your communication partner has to switch rx_adr and tx_adr!

const uint8_t channel=0x62;
const uint8_t rx_adr[5] = {0x12, 0xae, 0x31, 0xc4, 0x45};
const uint8_t tx_adr[5] = {0x24, 0xae, 0x31, 0xc4, 0x45};

uint8_t buffer[33];

void setup() {
  Serial.begin(9600);
  // RF24 and flash memory are using the same SPI interface 
  // The following two lines are turning the flash memory off
  // See: https://docs.arduino.cc/learn/communication/spi/
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  radio.begin();
  radio.setChannel(channel);
  radio.enableDynamicPayloads();
  radio.setCRCLength( RF24_CRC_16 ) ;
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.setRetries(15, 15);
  radio.setAutoAck(true);
  radio.openWritingPipe(tx_adr);
  radio.openReadingPipe(1,rx_adr);
  radio.startListening();
  Serial.println("Setup ok");
}

void loop() {
  uint8_t pipe_num, len, i;
  while( radio.available(&pipe_num) ) {
    len = radio.getDynamicPayloadSize();
    radio.read(buffer, len);    
    for (i = 0; i < len; i++) {
      Serial.write(buffer[i]);
    }
  }

  if(Serial.available()){
    Serial.print("sending ... ");
    radio.stopListening();
    i=0;
    while(Serial.available()){
      buffer[i]=Serial.read();
      i++;
      if(i>31){
        if(radio.write(buffer,i)){
          Serial.print("ok ...");
        } else {
          Serial.print("failed ...");
        }
        i=0;
      }
    }
    if(i>0){
        if(radio.write(buffer,i)){
          Serial.print("ok ...");
        } else {
          Serial.print("failed ...");
        }
    }
    Serial.println("done");
    radio.startListening();
  }
}
