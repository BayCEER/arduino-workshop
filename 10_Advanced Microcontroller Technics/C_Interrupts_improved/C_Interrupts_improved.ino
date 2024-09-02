// the volatile key word directs the compiler to load the variable from RAM and not from a storage register each time the variable is used
volatile uint8_t flag;

void schalter(void){
  flag=1;
}

const byte interruptPin = 2;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Starting...");
  attachInterrupt(digitalPinToInterrupt(interruptPin), schalter, FALLING);
}


void loop() {
  if(flag){
    Serial.println("INT0");
    delay(300);
    flag=0;
  }

}
