/*
* Reads and prints a RFID-Card UID 
* Uses SPI interface
* 
* Pinout:
* SS    10
* MOSI  11
* MISO  12
* SCK   13
* VCC   3.3V
* GND   GND 
*
* Modified sample sketch
* See: https://github.com/OSSLibraries/Arduino_MFRC522v2 for more information 
* 
*/

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>

MFRC522DriverPinSimple ss_pin(10); // Create pin driver. See typical pin layout above.

SPIClass &spiClass = SPI; 

const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0); // May have to be set if hardware is not fully compatible to Arduino specifications.

MFRC522DriverSPI driver(ss_pin, spiClass, spiSettings); // Create SPI driver.

MFRC522 mfrc522(driver); // Create MFRC522 instance.

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC for debugging.
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH); // Turn SPI-FLASH off, required on old boards only 

  while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4).
  mfrc522.PCD_Init();   // Init MFRC522 board.
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);	// Show details of PCD - MFRC522 Card Reader details.
	Serial.println(F("Scan PICC to see UID ..."));
}

void loop() {
	if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
		return;
	}    
  Serial.print("UID:");  
  MFRC522Debug::PrintSelectedUID(mfrc522, Serial);
  Serial.println();
}
