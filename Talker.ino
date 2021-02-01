#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <SD.h>
#include <SPI.h>
#include <FS.h>
#include <SPIFFS.h>
#include <LoRa.h>
#include <Wire.h>  
#include <WiFi.h>
#include <WiFiAP.h>
#include "SSD1306.h"
#include "tx.h"
#include "rx.h"
#include "config.h"
#include "fileIO.h"

void TaskTX( void *pvParameters );
void TaskRX( void *pvParameters );

#define FORMAT_SPIFFS_IF_FAILED true

// LoRa
#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  433E6
  
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(WELCOME_STRING);

  pinMode(16,OUTPUT);
  pinMode(2,OUTPUT);

  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  Serial.print("Initializing SPIFFS...");
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
    Serial.print("ERR");
    while (1);
  }
  writeFile(SPIFFS, FILENAME, " ");
  Serial.print("OK");
  Serial.println();

  Serial.print("Starting LoRa...");
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    Serial.print("ERR");
    while (1);
  }
  /*
  LoRa.setSyncWord(0xF3);
  LoRa.setTxPower(20); //2-20
  LoRa.setSpreadingFactor(10); //6-12
  LoRa.setCodingRate4(8); //5-8  
  LoRa.setSignalBandwidth(250E3);
  LoRa.enableCrc();
  */
  Serial.print("OK");
  Serial.println();

  Serial.print("Starting WiFi...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  Serial.print("OK");
  Serial.println();

  xTaskCreatePinnedToCore(
    TaskTX
    ,  "TaskTX"
    ,  8192
    ,  NULL
    ,  1
    ,  NULL 
    ,  0);

  xTaskCreatePinnedToCore(
    TaskRX
    ,  "TaskRX"
    ,  8192
    ,  NULL
    ,  1
    ,  NULL 
    ,  1);
}

void loop()
{
  // Empty. Things are done in Tasks.
}
