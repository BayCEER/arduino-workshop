
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  /* The constant LED_BUILTIN is the number of the pin to which the on-board LED is connected.
     This allows you to keep your code clean and readable. If you replace all ocurrencies of the constant 
     with an integer value of 5, your program would be the same.
  */
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);            // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);                       // turn the LED on (HIGH is the voltage level)
  delay(100);                                 // wait for a second
  digitalWrite(LED_BUILTIN, LOW);             // turn the LED off by making the voltage LOW
  if (digitalRead(3)) digitalWrite(4, HIGH);  // turn the LED off by making the voltage LOW
  delay(1000);
  if (digitalRead(3)) digitalWrite(6, HIGH);
  else digitalWrite(6, LOW);
}


/* Reference
https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
https://www.arduino.cc/reference/en/language/functions/time/delay/
https://www.arduino.cc/reference/en/language/variables/constants/ledbuiltin/
*/
