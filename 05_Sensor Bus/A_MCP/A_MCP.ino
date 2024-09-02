/*
 * Our board has the MCP3424 (analog-digital converter) built in. 
 * The microcontroller and the ADC communicate over the I2C bus
 * The actual I2C commands are outsourced to a class
 */

#include <Wire.h>
#include <MCP342x.h>

const byte addr = 0;    // for the board always 0
const uint8_t gain = 0; // 0-3: x1, x2, x4, x8
const uint8_t rate = 3; // resolution 0-3: 12bit ... 18bit
const uint8_t mode = 0; // 0 == one-shot mode - 1 == continuos mode
//  create an object of the class MCP342x
MCP342x mcp342x = MCP342x();
float span;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

}



void loop()
{
  Serial.print("mV:");
  for (uint8_t ch = 0; ch < 4; ch++) {
    //Start convertion 
    mcp342x.setConf(addr, 1, ch, mode, rate, gain);
    //wait until mcp3424 has finished the conversion
    delay(300);
    span = mcp342x.getData(addr);

    //print out results
    Serial.print("\t");
    Serial.print(span * 1000); //print out mV
  }
  Serial.println();
}


