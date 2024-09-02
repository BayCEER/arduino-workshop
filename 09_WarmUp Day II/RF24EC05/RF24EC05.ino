/*
 * Low Power ADC-Board
 * is a variant of BayEOS Low Power Board
 * 
 * It has 12 screw clamps
 * 1,7:       GRD
 * 2,8:       VCC
 * 3-5,9-11:  A0-A2,A3-A5
 * 6,12;      MOSFET Power switch via D7
 * 
 * For EC05 soil moisture sensors solder a 2.5V LDO voltageregulator on the board.
 * Exitation time must be lower then 10ms
 * 
 * VWC = 0.00119 * mV - 0.400
 * 
 *  
 */
#include<BayRF24.h>
#define RF24ADDRESS 0x45e3a1ae24LL
#define RF24CHANNEL 0x7e

BayRF24 client=BayRF24(9,10);

void setup(void){
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(7,OUTPUT);
  analogReference(INTERNAL);
  client.init(RF24ADDRESS,RF24CHANNEL);
}

void loop(void){
  digitalWrite(LED_BUILTIN,HIGH);
  digitalWrite(7,HIGH);
  delay(5); //Add a delay to allow sensors to power up
  float VWC;
  VWC = 0.00119*1100.0/1023*analogRead(A0)-0.400;
  digitalWrite(7,LOW);
  client.startDataFrame(BayEOS_Float32le,1);
  client.addChannelValue(VWC); 
  client.addChecksum(); 
  client.sendPayload();
  
  digitalWrite(LED_BUILTIN,LOW);
  
  delay(2000);
  
}
