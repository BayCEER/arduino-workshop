/****************************************************************
 * SHT21
 * The SHT2xSleep library already uses sleep mode. 
 * While the sensor performs the temperature or humidity conversion,
 * the microcontroller is asleep. More on this on the 2nd day...
 *
 ***************************************************************/

#include <Wire.h>
#include <Sleep.h>
#include <SHT2xSleep.h>

SIGNAL(TIMER2_OVF_vect){
}

void setup()
{
  Sleep.setupTimer2(2); //init timer2 to 0,0625sec
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Starting");
  delay(20);
}

void loop()
{
  unsigned long t=millis();
  float hum=SHT2x.GetHumidity();
  float temp=SHT2x.GetTemperature();
  SHT2x.reset();
  t=millis()-t;
  
  Serial.print("Humidity(%RH): ");
  Serial.print(hum);
  Serial.print("     Temperature(C): ");
  Serial.println(temp);
  Serial.print("cputime: ");
  Serial.println(t);
  
  delay(1000);
}

