#include <BayEOSBufferSPIFlash.h>
#include <BayDebug.h>



BayDebug client = BayDebug(Serial);
SPIFlash flash(8); //Standard SPIFlash Instanz
BayEOSBufferSPIFlash myBuffer; //BayEOS Buffer Instanz

void setup(void) {
  client.begin(9600, 1);
  Serial.print("Starting...");
  delay(10);
  myBuffer.init(flash); //This will restore old pointers
  //only stores Pointer positions each 10th write!
  //myBuffer.reset(); //This will set all pointers to zero
  client.setBuffer(myBuffer); //Connect buffer to transport client
}

int count=0;

void loop(void) {
  if ((count % 16) == 0){
    while(myBuffer.available())
      client.sendFromBuffer(); //Read data from buffer and try to send
  }

  if ((count % 2) == 0) {
    //Construct DataFrame
    client.startDataFrame(BayEOS_Float32le);
    client.addChannelValue(millis() );
    client.writeToBuffer();
  }
  delay(1000);
  count++;
}
/* 
  Reference
  https://www.arduino.cc/reference/en/language/functions/time/millis/
*/

