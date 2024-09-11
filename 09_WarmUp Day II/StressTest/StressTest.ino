/**
 * Plug in one wire in A1 and leave the other end free
 * Plug in one wire in GND and leave the other end free
 * 
 * take the free cable ends between your thumb and forefinger and 
 * watch the serial output :-)
 * 
 * 
*/


void setup() {
  pinMode(A1, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int s = analogRead(A1);
  if (s > 1022) {
    Serial.println("Please touch the cable ends.");
  } else if (s<=1022 && s > 950){
    Serial.println("Iceman!"); 
  } else if (s<=950 && s > 900 ){
    Serial.println("Quite relaxed!");
  } else {
    Serial.println("You need some coffee!");
  }
 

  delay(500);
  
}
