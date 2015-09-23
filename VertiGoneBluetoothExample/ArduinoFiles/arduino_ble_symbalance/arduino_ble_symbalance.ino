#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "Adafruit_BluefruitLE_SPI.h"
#define RTS  10
#define RXI  11
#define TXO  12
#define CTS  13
#define MODE -1

#define BUFSIZE 128
#define VERBOSE_MODE false
Adafruit_BNO055 bno = Adafruit_BNO055(55);
//SoftwareSerial bluefruitSS = SoftwareSerial(TXO, RXI);
//Adafruit_BluefruitLE_UART ble(bluefruitSS, MODE, CTS, RTS);
#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4    // Optional but recommended, set to -1 if unused
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
int battery = 0;
int count = 0;

void setup() {

  Serial.begin(115200);
  Serial.println(F("BLE Starting"));

  delay(5000);

  if (! ble.begin(VERBOSE_MODE)) {
    Serial.println( F("FAILED!") );
    while(1);
  }

  Serial.println( F("OK!") );

  Serial.print(F("Factory reset: "));
  if(! ble.factoryReset()) {
    Serial.println(F("FAILED."));
    while(1);
  }

  Serial.println( F("OK!") );

  ble.echo(false);

  Serial.print(F("Set device name: "));
  if(! ble.sendCommandCheckOK(F("AT+GAPDEVNAME=SYMBIO"))) {
    Serial.println(F("FAILED."));
    while(1);
  }

  Serial.println(F("OK!"));

  ble.reset();

  Serial.print(F("BNO055 init: "));
  if(! bno.begin()) {
    Serial.println(F("FAILED."));
    while(1);
  }

  Serial.println(F("OK!"));

  bno.setExtCrystalUse(true);

  while (! ble.isConnected())
    delay(500);

  Serial.println(F("Connected"));

  batteryLevel();
  for (int i = 0; i < 10; i++) {
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);              // wait for a second
      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
      delay(100);   
  }
}

void loop() {

  sensors_event_t event;
  bno.getEvent(&event);
//  imu::Quaternion quat = bno.getQuat();
//  ble.print("AT+BLEUARTTX=");
//  ble.print(quat.w(), 4);
//  ble.print(",");
//  ble.print(quat.x(), 4);
//  ble.print(",");
//  ble.print(quat.y(), 4);
//  ble.print(",");
//  ble.print(quat.z(), 4);
//  ble.println(":");
//  ble.readline(200);
//  ble.waitForOK();
//  delay(200);
  ble.print("AT+BLEUARTTX=");
  ble.print(event.orientation.x, 1);
  ble.print(",");
  ble.print(event.orientation.y, 1);
  ble.print(",");
  ble.println(event.orientation.z, 1);
  ble.waitForOK();
  delay(200);
/*
  if(count == 5000) {
    batteryLevel();
    count = 0;
  } else {
    delay(200);
    count++;
  }
*/
}

void batteryLevel() {

  ble.println("AT+HWVBAT");
  ble.readline(1000);

  if(strcmp(ble.buffer, "OK") == 0) {
    battery = 0;
  } else {
    battery = atoi(ble.buffer);
    ble.waitForOK();
  }

}
