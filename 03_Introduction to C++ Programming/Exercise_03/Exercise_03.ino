int i = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  i = i+100;
  if (i%1000 == 0) Serial.println(i);

}
