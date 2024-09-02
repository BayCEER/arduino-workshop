char t = 'a';
long l = 10;
int i = -1;
float f = 1.02;
boolean b = true;

void setup() {
   Serial.begin(9600);
}

void loop() {
  Serial.println(t);
  Serial.println(l);
  Serial.println(i);
  Serial.println(f);
  Serial.println(b);

  // Wait for one second
  delay(1000);
  
}

