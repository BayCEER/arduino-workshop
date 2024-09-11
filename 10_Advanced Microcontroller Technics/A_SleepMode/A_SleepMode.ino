/***********************************************************
Power down the ATMEGA to SLEEP_MODE_PWR_SAVE

ATMEGA will consume about 1µA

IMPORTANT!!
You will need a 32.768kHz Quarz connected!!

***********************************************************/

#include <Sleep.h>

volatile unsigned long seconds = 0;


//The very important 32.768kHz interrupt handler
ISR(TIMER2_OVF_vect){
  seconds += 1; //Adjust to your timer2 time!
}


void setup(void)
{
//  pinMode(10, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting ...");
  delay(100);
  Sleep.setupTimer2(); //init timer2 to 1 sec
}

void loop(void)
{
  // Output each 16 secs
  if((seconds%16)==0){
    Serial.println("Awake ...");
    Serial.print("Runtime:");
    Serial.println(seconds);
  
    Serial.print("CPU-Time:");
    Serial.println(millis());
    Serial.println("Entering Sleep mode");
    
    Serial.flush();
  }
  Sleep.sleep(TIMER2_ON,SLEEP_MODE_PWR_SAVE);     // sleep function called here
}


/*
 * C++ - Knowledge
 * - volatile == flüchtig - Important if variable is modified by an interrupt routine
 * - ISR == Interrupt Service Routine
 * - Sleep-Class
 */

