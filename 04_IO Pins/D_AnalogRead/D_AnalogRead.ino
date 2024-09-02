void setup() {
  Serial.begin(9600);
}

void loop() {
  int adc=analogRead(A0);
  Serial.println(3.3*adc/1023);
  delay(500);  
}

//TODO
  // 1.	What happens if the input is not connected?
  // 2.	What output value is produced when A1 is connected to GND?
  // 3.	What output value is produced when A1 is connected to VCC?  
  // 4.	Connect the resistor thermistor (20 KOhm)
  //   a.	Calculate the resistance of the thermistor
  //   b.	Calculate the temperature with a polynomial


/* References
    https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
*/
