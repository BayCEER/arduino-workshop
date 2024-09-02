
void setup() {
  Serial.begin(9600);
  // Siedepunkt 100°C
  Serial.println(ftoc(212));
  // Gefrierpunkt 0°C
  Serial.println(ftoc(32));
}

void loop() {
 
}

float ftoc(float f){
  return (f-32)*5/9;
}


