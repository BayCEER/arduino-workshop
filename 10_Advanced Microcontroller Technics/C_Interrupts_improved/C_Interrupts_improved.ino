// volatile variable
// "volatile" tells the compiler that it has to read
// the variable each time from memory because it might have
// been modified by a ISR (Interrupt Service Routine)
volatile int count;
volatile uint8_t flag;

void schalter(void) {
  if(! flag) count++;
  flag = 1;
}

const byte interruptPin = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), schalter, FALLING);
  delay(1);
  flag=0;
  count=0;
}


void loop() {
  Serial.print("start loop .. ");
  for (uint8_t i = 0; i < 5; i++) {
    Serial.print(i);
    Serial.print(" .. ");
    delay(500);
  }
  if (flag) {
    Serial.print(" (INT0 - ");
    Serial.print(count);
    Serial.print(") ");
    delay(300);
    flag = 0;
  }
  Serial.println("end loop");
}
