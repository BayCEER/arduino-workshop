void setup() {
  Serial.begin(9600);
}

void loop() {
  int s = analogRead(A1);
  if (s < 2) {
    Serial.println("Please touch the cable.");
  } else if (s>=2 && s < 50){
    Serial.println("Iceman!"); 
  } else if (s>=50 && s < 100){
    Serial.println("Quite relaxed!");
  } else {
    Serial.println("You need a break!");
  }
 

  delay(500);
  
}
