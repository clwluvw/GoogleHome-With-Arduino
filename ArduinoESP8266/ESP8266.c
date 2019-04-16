#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

const char* ssid     = "WiFiSSID";
const char* password = "WiFiPassword";
char path[] = "/";
char host[] = "YOUR_HOST";
  
WebSocketClient webSocketClient;
WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  
  if (client.connect(host, 8011)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 1); //1 is off, 0 is on
}

int goNext(String str, int index)
{
  for (int i = index; i < str.length(); i++)
  {
    if (str[i] == ':')
      return i;
  }
  return -1;
}

void loop() {
  String data;

  if (client.connected()) {
    
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
      int id = -1, state = -1;
      int i = goNext(data, 0);
      if (i >= 0) {
        for (int j = i+2; j < data.length(); j++) {
          if (data[j] == ',') {
            break;
          }
          if (id < 0)
            id = 0;
          id *= 10;
          id += ((int)(data[j]) - 48);
        }
      }
      i = goNext(data, i + 1);
      if (i >= 0)
      {
        for (int j = i+2; j < data.length(); j++)
        {
          if (data[j] == ',') {
            break;
          }
          if (state < 0)
            state = 0;
          state *= 10;
          state += data[j] - 48;
        }
      }
      Serial.println("results : ");
      Serial.println(id);
      Serial.println(state);

      if (id == 1 && state == 1) {
        digitalWrite(LED_BUILTIN, 0);
      }
      else if (id == 1 && state == 0) {
        digitalWrite(LED_BUILTIN, 1);
      }
    }

    webSocketClient.sendData("Sent from esp8266");
    
  } else {
    Serial.println("Client disconnected.");
  }
  
  delay(3000);
  
}