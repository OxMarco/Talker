# Talker
A simple dual-channel radio communication system over LoRa.

## Why
There are several projects attempting at creating communication systems with LoRa and cheap hardware such as the ESP32 or the TTGO devices, Meshtastic and Disaster Radio to name a few. Despite being excellent examples of Open Source software, they all end up being too complex for the average user, with the need of advanced configuration, special hardware and complicated debugging.

This project was born to **make things extremely simple**, an almost **turnkey solution** at a competing price. Chat with your friend(s) a few km away without using cellular connection, smoke signals or a walkie-talkie.

## How
Talker is based on the TTGO LoRa32 board, an ESP32 with a LoRa transceiver and an OLED display. In addition to that, it heavily relies on a device with a screen and WiFi: it can be a smartphone, tablet or pc, new/old it doesn't matter as the web interface can be rendered on IExplorer too. Simply connect to the device WiFi, navigate to the internal IP *192.168.4.1* and send messages. Refresh the page to receive new messages

To extend the range you can wiggle LoRa settings like spreading factor, bandwidth, coding rate, use better antennae or add a middlepoint repeater (currently in brewing).

## ToDo
* Implement location messages using Javascript *mobile Geolocation API*
* Improve UI
* On screen diagnostics
* Use *Event Source* for new incoming messages
