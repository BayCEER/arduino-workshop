#include <BayEOSBufferRAM.h>
#include <BayRF24.h>
#include <Sleep.h>
#include <RTClib.h>

#define RF24CHANNEL 0x2b /* A */
// #define RF24CHANNEL 0x2b /* B */
#define RF24ADDRESS 0xf36c437912 /* A0 or B0 */
// #define RF24ADDRESS 0xf36c437924 /* A1 or B1 */
// #define RF24ADDRESS 0xf36c437948 /* A2 or B2 */
// #define RF24ADDRESS 0xf36c437996 /* A3 or B3 */
// #define RF24ADDRESS 0xf36c4379ab /* A4 or B4 */
// #define RF24ADDRESS 0xf36c4379bf /* A5 or B5 */

#define BUFFER_SIZE 1000
uint8_t buffer[BUFFER_SIZE];
BayEOSBufferRAM myBuffer(buffer,BUFFER_SIZE);

BayRF24 client=BayRF24(9,10);

RTC_Timer2 myRTC;

ISR(TIMER2_OVF_vect) {
  myRTC._seconds += 1; // increment clock by 1 second
}



void setup(void) {

  // Deactivate Flash Storage on SPI bus
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin(9600);
  Serial.print("Starting...");
  myBuffer.setRTC(myRTC, 0); //RTC relative!
// The usage of the RTC is necessary because the millis() timer is in sleep-mode.
// A calculation of the delay based on millis() would produce wrong (too short) time values. 
// RTC is driven by ISR and has a resolution of seconds 
  client.setBuffer(myBuffer);
  client.init(RF24ADDRESS,RF24CHANNEL);
  Sleep.setupTimer2(); //init timer2 to 1 sec
  Serial.print("Done");
  delay(100);
}

void loop(void) {

  if ((myRTC._seconds % 8) == 1) {
    // delay(200);
    // DataFrame construction
    client.startDataFrame(BayEOS_Float32le);
    client.addChannelValue(millis());
    client.addChannelValue(myRTC._seconds);
    client.sendOrBuffer();
  }

  if ((myRTC._seconds % 2) == 0) {
    client.sendFromBuffer();
  }
  
  Sleep.sleep(TIMER2_ON, SLEEP_MODE_PWR_SAVE);    // sleep function called here


}
