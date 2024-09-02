/*
 * Communication between two Arduinos by SoftwareSerial
 * 
 * Cross over wiring:
 * 
 * Board1   Board2
 *  GND  --  GND
 *   2   --   3
 *   3   --   2
 * 
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
  Serial.println("Bereit für Eingaben");
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

