#ifndef RX_H
#define RX_H

#include "config.h"
#include "fileIO.h"

void TaskRX(void *pvParameters)
{
  (void) pvParameters;

  SSD1306 screen(0x3c, 21, 22);

  screen.init();
  screen.flipScreenVertically();  
  screen.setFont(ArialMT_Plain_10);
  screen.setTextAlignment(TEXT_ALIGN_LEFT);
  screen.drawString(0, 0, WELCOME_STRING);
  screen.drawString(0, 15, "WiFi Settings");
  screen.drawString(0, 30, ssid);
  screen.drawString(0, 45, pass);
  screen.display();

  Serial.print("RX Task ready - core #");
  Serial.print(xPortGetCoreID());
  Serial.println();

  while(true) {
    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
      // received a packet
      Serial.print("Received packet");

      // read packet header bytes:
      int recipient = LoRa.read();          // recipient address
      byte sender = LoRa.read();            // sender address
      byte incomingMsgId = LoRa.read();     // incoming msg ID
      byte incomingLength = LoRa.read();    // incoming msg length

      String incoming = "";

      while (LoRa.available()) {
        incoming += (char)LoRa.read();
      }

      if (incomingLength != incoming.length()) { // check length for error
        Serial.println("error: message length does not match length");
        continue;  // skip rest of the cycle
      }

      // if the recipient isn't this device or broadcast,
      if (recipient != FROM_ADDR && recipient != ALL) {
        Serial.println("This message is not for me.");
        continue;  // skip rest of the cycle
      }

      // Save msg
      String temp = "<li class='you'>"+incoming+"</li>";
      appendFile(SPIFFS, FILENAME, temp.c_str());

      // if message is for this device, or broadcast, print details:
      Serial.println("Message: " + incoming);
      Serial.println("RSSI: " + String(LoRa.packetRssi()));
      Serial.println("SNR: " + String(LoRa.packetSnr()));
      Serial.println();

      screen.clear();
      screen.setTextAlignment(TEXT_ALIGN_LEFT);
      screen.setFont(ArialMT_Plain_10);
      screen.drawString(0, 0, "Received Message:");
      screen.drawString(0, 15, incoming);
      screen.display();
    }
    
    vTaskDelay(10);
  }
}

#endif // RX_H
