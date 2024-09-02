void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  fade(5,100);
  fade(-5,100);
}

void fade(int step, int wait){  
  for(int d = step>0 ? 0 : 255; d >= 0 && d <= 255; d = d + step){
      analogWrite(LED_BUILTIN,d);
      delay(wait);
  }
 }