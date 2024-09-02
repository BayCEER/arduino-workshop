volatile int count; 

void schalter(void){
  count++;
  Serial.println("INT0");
  Serial.println(count);
}

const byte interruptPin = 2;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Starting...");
  attachInterrupt(digitalPinToInterrupt(interruptPin), schalter, FALLING);
}


void loop() {
  // put your main code here, to run repeatedly:

}
