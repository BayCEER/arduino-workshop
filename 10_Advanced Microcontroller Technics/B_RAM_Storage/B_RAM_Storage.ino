#include <BayEOSBufferRAM.h>
#include <BayDebug.h>



BayDebug client = BayDebug(Serial);

// Create a RAM-Buffer 
// Each Frame is composed of 12 Bytes: 
// 4 (Timestamp) + 1 (Length) + 3 (FrameHeader) + 4 (je Channel)

//TODO: Reduce the size
#define BUFFER_SIZE 50
uint8_t buffer[BUFFER_SIZE];
BayEOSBufferRAM myBuffer(buffer,BUFFER_SIZE);

void setup(void) {
  client.begin(9600, 1);
  Serial.println("Starting...");
  delay(10);
  client.setBuffer(myBuffer);
}

int count=0;

void loop(void) {
  if ((count % 16) == 0){
    while(myBuffer.available())
      client.sendFromBuffer();
  }

  if ((count % 2) == 0) {
    //Construct DataFrame
    client.startDataFrame(BayEOS_Float32le);
    client.addChannelValue(millis());
    client.writeToBuffer();
  }
  delay(1000);
  count++;
}
