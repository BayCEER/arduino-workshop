/* 
   This program shows how to manage multiple OneWire sensors on one bus. 
   Each sensor has a unique RAM address. These are assigned to a channel number (1, 2, 3...) in the order 
   in which they are connected. 
   The mapping is stored in the microcontroller's EEPROM and is restored at each startup. 
   Again, most of the logic is outsourced to a class.
*/
#include <OneWire.h>
#include <EEPROM.h>
#include <DS18B20.h>



/*
  Create a DS18B20 instance on pin 4, offset 0 and a
  capacity of 4 Sensors
*/
DS18B20 ds=DS18B20(4,0,4);



uint8_t startup=1;
const byte* new_addr;
uint8_t channel;
float temp;



void setup(void){
  Serial.begin(9600);
  pinMode(4,INPUT_PULLUP);
}

void loop(void){
  if(startup){
    startup=0;
    Serial.print("Arduino startup: DS18B20 channels: ");
    Serial.print(ds.getNumberOfChannels(),DEC);
    Serial.print(" - registered ");
    Serial.print(ds.setAllAddrFromEEPROM(),DEC);
    Serial.print(" Sensors from EEPROM");
    Serial.println();
  }
  ds.t_conversion();
  delay(1000);
   Serial.print("Reading sensors...");
   Serial.println();
   while(channel=ds.getNextChannel()){
       if(! ds.readChannel(channel,&temp)){
         Serial.print("Channel ");
         Serial.print(channel,DEC);
         Serial.print(": ");
         Serial.print(temp);
         Serial.print("C");
         Serial.println();
       }
   }
   Serial.println();
   
// Search and Delete

    Serial.print("Searching for non responding sensors");
    Serial.println();

    while(channel=ds.checkSensors()){
      new_addr=ds.getChannelAddress(channel);

      Serial.print("Channel ");
      Serial.print(channel,DEC);
      Serial.print(" with ROM ");
      Serial.print(ds.addr2String(new_addr));
      Serial.print(" is not responding. Deleting ...");
      Serial.println();
      if(! ds.deleteChannel(new_addr)){
        Serial.print("Failed to delete sensor on channel ");
        Serial.print(channel, DEC);
        Serial.println();
     }
   }
  
  Serial.print("Searching for new sensors");
  Serial.println();
  while(new_addr=ds.search()){
    if(channel=ds.getNextFreeChannel()){
      ds.addSensor(new_addr,channel);
      Serial.print("Registered new sensor with ROM ");
      Serial.print(ds.addr2String(new_addr));
      Serial.print(" on channel ");
      Serial.print(channel,DEC);
      Serial.println();
      } else {
        Serial.print("Failed to add new sensor with ROM ");
        Serial.print(ds.addr2String(new_addr));
        Serial.print(": No channel left!!");
        Serial.println();
        break;
      }
  }
}
