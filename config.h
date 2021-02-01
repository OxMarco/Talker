#ifndef CONFIG_H
#define CONFIG_H

#define ALL 0X00
#define FILENAME "/msgs.txt"

#define TALKER2
#ifdef TALKER1
  #define WELCOME_STRING "Radio #1 - Ready"
  #define FROM_ADDR 0xBB
  #define TO_ADDR 0xFF
  const char* ssid = "radio-001";
  const char* pass = "password";
#else // TALKER2
  #define WELCOME_STRING "Radio #2 - Ready"
  #define FROM_ADDR 0xFF
  #define TO_ADDR 0xBB
  const char* ssid = "radio-002";
  const char* pass = "password";
#endif

#endif // CONFIG_H
