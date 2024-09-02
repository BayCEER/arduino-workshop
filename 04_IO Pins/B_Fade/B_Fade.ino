void setup() {
  pinMode(LED_BUILTIN,OUTPUT);   
}

void loop() {
  // fade in 
  for (int d = 0 ; d <= 255; d+=5) {
    analogWrite(LED_BUILTIN, d);    
    delay(100);
  }
  // fade out 
  for (int d = 255 ; d >= 0; d-=5) {
    analogWrite(LED_BUILTIN, d);
    delay(100);
  }
}

/* 
 * TODO: Change the number 255 to 400 and re-upload the sketch - What happens?
 */


 /* Reference
 *  https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/    
 */