/*********************************************************************
This is an example for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

// This version uses the internal data queing so you can treat it like Serial (kinda)!

#include <SPI.h>
#include "Adafruit_BLE_UART.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{ 
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

  BTLEserial.setDeviceName("VGONE"); //THIS MUST BE "VGONE" TO BE PICKED UP! * 7 characters max! */

  BTLEserial.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

long getDecimal(float val)
{
 int intPart = int(val);
 long decPart = 1000*(val-intPart); //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places
                                   //Change to match the number of decimal places you need
 if(decPart>0)return(decPart);           //return the decimal part of float number if it is available 
 else if(decPart<0) return((-1)*decPart); //if negative, multiply by -1
 else if(decPart=0) return(00);           //return 0 if decimal part of float number is not available
}

String floatToString(float f) {
 String stringVal = "";
  stringVal += String(int(f))+ "." + String(getDecimal(f)); 
  return stringVal;
} 

void sendStringToBle(String s) {
   uint8_t sendbuffer[20];
   s.getBytes(sendbuffer, 20);
   char sendbuffersize = min(20, s.length());

   Serial.print(F("\n* Sending -> \"")); Serial.print((char *)sendbuffer); Serial.println("\"");

   // write the data
   BTLEserial.write(sendbuffer, sendbuffersize);
}

void loop()
{
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();
  
  //Change this code to your gyroscope/accelerometer data, 20 bytes at a time
  
  //Example: Send accelerometer data by PREFIXING string with "A"
  sendStringToBle("100,1503,3004");
  
  //Example: Send gyroscope data by sending string with NO PREFIX
  sendStringToBle("A160,15603,30604");
}
