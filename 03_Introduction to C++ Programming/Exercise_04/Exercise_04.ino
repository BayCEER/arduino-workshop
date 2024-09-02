void setup() {
   Serial.begin(9600);
   for (int i = 1; i < 6; i++) {  
      Serial.print("i:");  
      Serial.println(i*i);  
  }  
}

void loop() {
  
}
