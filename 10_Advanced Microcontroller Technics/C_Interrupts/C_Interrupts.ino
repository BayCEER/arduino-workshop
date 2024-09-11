// volatile variable
// "volatile" tells the compiler that it has to read
// the variable each time from memory because it might have
// been modified by a ISR (Interrupt Service Routine)
volatile int count;

// Function called when the Interrupt is fired
void schalter(void) {
  count++;
  Serial.print(" (INT0 - ");
  Serial.print(count);
  Serial.print(") ");
}

// External Interrupts are possible on PIN 2 (==INT0) and PIN 3 (==INT1)
// we use pin 2
const byte interruptPin = 2;
void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  pinMode(interruptPin, INPUT_PULLUP);  //activate pullup resistor. So the pin is in state 1 when not connected
  attachInterrupt(digitalPinToInterrupt(interruptPin), schalter, FALLING);
}


void loop() {
  Serial.print("start loop .. ");
  for (uint8_t i = 0; i < 5; i++) {
    Serial.print(i);
    Serial.print(" .. ");
    delay(500);
  }
  Serial.println("end loop");
}
