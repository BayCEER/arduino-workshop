#define LED 5
#define SWITCH 4

void setup() {
  pinMode(LED,OUTPUT);
//  pinMode(SWITCH,INPUT);// optional, because default mode
//  digitalWrite(SWITCH,HIGH); // Turn pullup (~47k) on
  pinMode(SWITCH,INPUT_PULLUP);
}

void loop() {
  digitalWrite(LED,digitalRead(SWITCH));  
}

// TODO: 
// 1. Modify the program to flash the LED if GND - SWITCH PIN is connected
// 2. Test your program changes 

/* References
   https://www.arduino.cc/reference/en/language/structure/further-syntax/define/
   https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
   https://www.arduino.cc/reference/en/language/structure/boolean-operators/logicalnot/
*/

