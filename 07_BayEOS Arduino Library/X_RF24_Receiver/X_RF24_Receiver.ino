#include <BayDebug.h>
#include <BaySerial.h>

#define DEBUG_OUTPUT 0

#if DEBUG_OUTPUT
BayDebug client(Serial);
#else
BaySerial client(Serial);
#endif

#include <RF24.h>
RF24 radio(9,10);
const uint8_t pipes[6][5] = { 
    {0x12, 0xae, 0x31, 0xc4, 0x45},
    {0x24, 0xae, 0x31, 0xc4, 0x45},
    {0x48},{0x96},{0xab},{0xbf}
};


#include <printf.h>

void setup(void) {
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH); // Turn SPI-FLASH off, required on old boards only 
  radio.begin();
  radio.setChannel(0x6e);
  radio.setPayloadSize(32);
  radio.enableDynamicPayloads();
  radio.setCRCLength( RF24_CRC_16 ) ;
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setRetries(15, 15);
  radio.setAutoAck(true);
  //radio.openWritingPipe(pipes[0]);
  for (uint8_t i = 0; i < 6; i++) {
    radio.openReadingPipe(i, pipes[i]);
  }
#if DEBUG_OUTPUT
  client.begin(9600, 1);
#else
  client.begin(38400);
#endif

  printf_begin();
  Serial.println("Starting");
  radio.printDetails();
  Serial.println("------------");
  client.sendMessage("RF24-Router started");
  radio.startListening();

}

uint8_t nrf_payload[32];
String origin="RF-x";

void loop(void) {
  uint8_t pipe_num, len;
  while( radio.available(&pipe_num) ) {
 //   client.startRoutedFrame(pipe_num, 0);
    origin[3]='0'+pipe_num;
    client.startOriginFrame(origin,1);
    len = radio.getDynamicPayloadSize();
    radio.read(nrf_payload, len);
//    Serial.print("GOT: ");
    for (uint8_t i = 0; i < len; i++) {
//      Serial.print(nrf_payload[i], HEX);
      client.addToPayload(nrf_payload[i]);
    }
//    Serial.println();
    client.sendPayload();
  }
  delay(1);
}
