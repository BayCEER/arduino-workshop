/****************************************************
  This is a example sketch for using GPRS with
  LOW POWER CONSUMPTION
  GPRS-MODEM will get switched off totally by MOSFET
  Sending occurs only once an hour

*****************************************************/

#include <BayEOSBufferSPIFlash.h>
#include <Sleep.h>
#include <RTClib.h>
#include <BaySIM800.h>
BaySIM800 client = BaySIM800(Serial);
#define SIM800_CONFIG "http://132.180.112.128/gateway/frame/saveFlat|import@Workshop|ChangeME|MyGPRS-Board|iot.1nce.net||||"

#define GPRS_POWER_PIN 7

SPIFlash flash(8); //Standard SPIFlash Instanz
BayEOSBufferSPIFlash myBuffer; //BayEOS Buffer
RTC_Timer2 myRTC;
volatile uint8_t seconds = 0;
ISR(TIMER2_OVF_vect) {
  seconds += 1; //
}


// we will collect 60 measurements before we try to send
uint16_t gprs_counter = 0;
uint8_t gprs_status = 0;
#define GPRS_SEND_COUNT 60
uint8_t tx_error = 0;

void setup()
{
  myBuffer.init(flash);
  myBuffer.setRTC(myRTC, 0); //RTC usage is relative!
  client.setBuffer(myBuffer);
  Sleep.setupTimer2(); //init timer2 to 1 sec

  pinMode(GPRS_POWER_PIN, OUTPUT);
  digitalWrite(GPRS_POWER_PIN, HIGH);
  //CHANGE CONFIG!!
  client.readConfigFromStringPGM(PSTR(SIM800_CONFIG));
  client.begin(38400);
  client.sendMessage("GPRS started");
  digitalWrite(GPRS_POWER_PIN, LOW);
  gprs_counter=GPRS_SEND_COUNT - 1;
}


void loop()
{
  if (seconds) {
    myRTC._seconds += seconds;
    seconds = 0;
  }

  if ((myRTC._seconds % 16) == 1) {
    //Construct DataFrame
    client.startDataFrame(BayEOS_Float32le);
    client.addChannelValue(millis());
    client.addChannelValue(myRTC._seconds);
    client.writeToBuffer();
  }

  if ((myRTC._seconds % 32) == 2) {
    gprs_counter++;
    if (gprs_counter > GPRS_SEND_COUNT) {
      if (! gprs_status) {
        digitalWrite(GPRS_POWER_PIN, HIGH);
        client.begin(38400);
        gprs_status = 1;
      }
      if (client.sendMultiFromBuffer(2000)) tx_error++;
      else tx_error = 0;

      if (tx_error > 5 || ! myBuffer.available()) {
        gprs_counter = 0;
        gprs_status = 0;
        tx_error = 0;
        digitalWrite(GPRS_POWER_PIN, LOW);
        Serial.end();
        pinMode(1, INPUT);
      }
    }
  }

  Sleep.sleep(TIMER2_ON, SLEEP_MODE_PWR_SAVE);    // sleep function called here
}


