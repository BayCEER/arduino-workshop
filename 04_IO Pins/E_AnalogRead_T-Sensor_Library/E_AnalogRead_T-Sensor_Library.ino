#include <ntc_R2T.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adc=analogRead(A1);
  float rt=20000.0/(1023.0/adc-1);
  Serial.println(ntc10_R2T(rt));
  delay(500);
}

// TODO: 
// 1. Download the ntc R2T library from our e-Learning site 
// 2. Install the library