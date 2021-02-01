#ifndef TX_H
#define TX_H

#include "config.h"
#include "fileIO.h"
#include "page.h"

// Global flag and buffer
bool msg_ready = false;
String outgoing = "";

void TaskTX(void *pvParameters)
{
  (void) pvParameters;

  unsigned long int msgCount = 0;
  AsyncWebServer http_server(80);

  Serial.print("Starting web server...");

  http_server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Page not found!");
  });

  http_server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String page = PAGE_HEADER;
    String messages = readFile(SPIFFS, FILENAME);
    page += messages;
    page += PAGE_FOOTER;
    request->send_P(200, "text/html", page.c_str());
  });

  http_server.on("/clear", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("/");
  });

  http_server.on("/send", HTTP_POST, [](AsyncWebServerRequest *request){
      if(!request->hasParam("msg", true)) {
        request->send(422, "text/plain", "No msg sent!");
      } else {
        AsyncWebParameter* p = request->getParam("msg", true);
        outgoing = p->value().c_str();
        msg_ready = true;

        // Save msg
        String temp = "<li class='me'>"+outgoing+"</li>";
        appendFile(SPIFFS, FILENAME, temp.c_str());
   
        request->redirect("/");
      }
  });

  http_server.begin();
  Serial.print("OK");
  Serial.println();

  Serial.print("TX Task ready - core #");
  Serial.print(xPortGetCoreID());
  Serial.println();

  while(true) {
 
    while (LoRa.beginPacket() == 0) {
      Serial.println("... waiting for transmitting msg ...");
      vTaskDelay(100);
    }

    if(msg_ready) {
      Serial.print("Sending MSG...");

      LoRa.beginPacket();  // start packet
      LoRa.write(TO_ADDR);  // add destination address
      LoRa.write(FROM_ADDR);  // add sender address
      LoRa.write(++msgCount);  // add message ID
      LoRa.write(outgoing.length());  // add payload length
      LoRa.print(outgoing);  // add payload
      LoRa.endPacket(true);  // finish packet and send it
       
      Serial.print("OK");
      Serial.println();

      msg_ready = false;
      outgoing = "";
    }

    vTaskDelay(10);
  }
}

#endif // TX_H
