#include <math.h>

/* 
 *  Conversion function resistance (ohms) to temperature (°C)
 *  The function was created by a polynomial adjustment: T~ln(r)
 */
float ntc10_R2T(float r) {
  float log_r = log(r);
  return 440.61073 - 75.69303 * log_r +
         4.20199 * log_r * log_r - 0.09586 * log_r * log_r * log_r;
}


void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  int adc=analogRead(A0);
  float rt=20000.0/(1023.0/adc-1);
  float temp=ntc10_R2T(rt);
  Serial.println(temp);
  if(temp<26){
    digitalWrite(4,HIGH);
    digitalWrite(6,LOW);
  } else if(temp<28){
    digitalWrite(4,LOW);
    digitalWrite(6,LOW);
  } else {
    digitalWrite(4,LOW);
    digitalWrite(6,HIGH);
  }
  delay(500);

}