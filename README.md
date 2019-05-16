# Google Home with Arduino
This project contains Node.js Express & WebSocket for getting request from IFTTT Webhook service and send it to ESP8266 WebSocket Client for changing light state on/off

ESP8266 codes stored in `ArduinoESP8266` directory

Server codes stored in `Server` directory

# Server Setup
       node index.js

# Arduino ESP8266 Setup
1. Open up Arduino, then go to the Preferences (File > Preferences). Then, towards the bottom of the window, copy 'http://arduino.esp8266.com/stable/package_esp8266com_index.json' into the "Additional Board Manager URLs"
    * If you already have a URL in there, and want to keep it, you can separate multiple URLs by placing a comma between them.
1. Hit OK. Then navigate to the Board Manager by going to Tools > Boards > Boards Manager. There should be a couple new entries in addition to the standard Arduino boards. Look for esp8266. Click on that entry, then select Install.
    * More information: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon

1. Add `ArduinoESP8266/ESP8266-Websocket` to Arduino libraries
    * https://github.com/morrissinger/ESP8266-Websocket
1. Config your Wifi and your server informations in `ArduinoESP8266/ESP8266-Websocket/ESP8266.c`

# IFTTT Setup
1. Link your Google Assistant to your IFTTT account
1. Create Webhook Alphabet in your IFTTT account
1. configure it with your <your_ip_or_domain>/config/?lampID=<lamp_num_in_index.js>&state=<on_or_off>
