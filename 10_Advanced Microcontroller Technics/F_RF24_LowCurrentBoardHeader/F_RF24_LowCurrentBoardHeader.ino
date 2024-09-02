#define SAMPLING_INT 10
#define RF24CHANNEL 0x4e
#define RF24ADDRESS 0x45c431ae48LL

#include <BayEOSBufferSPIFlash.h>

SPIFlash flash(8);
BayEOSBufferSPIFlash myBuffer;

#include <BayRF24.h>
BayRF24 client = BayRF24(9, 10);

#include <LowCurrentBoard.h>

void setup()
{
  client.init(RF24ADDRESS, RF24CHANNEL);
  myBuffer.init(flash); //This will restore old pointers
  //myBuffer.reset(); //This will set all pointers to zero
  myBuffer.skip(); //This will move read pointer to write pointer
  myBuffer.setRTC(myRTC, 0); //Nutze RTC relativ!
  client.setBuffer(myBuffer, 120); //use skip!
  initLCB(); //init RTC (timer2), LED
  startLCB(); // the status LED is blinking 3x
}


void loop() {
  if (ISSET_ACTION(0)) {
    UNSET_ACTION(0);
    //eg measurement
    client.startDataFrame(BayEOS_Int16le,1); // "0: without checksum, 1: checksum"
    client.addChannelValue(millis());
    client.addChecksum();
    sendOrBufferLCB(); 
    /* 
      A feedback is provided for the first ten calls by the LED:
        success:  blinking 1x 
        error:    blinking 2x 
    */

  }

  if (ISSET_ACTION(7)) {
    UNSET_ACTION(7);
    client.sendFromBuffer();
  }
  sleepLCB();

}
