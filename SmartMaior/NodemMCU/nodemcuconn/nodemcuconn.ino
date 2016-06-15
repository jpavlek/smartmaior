#include <ESP8266WiFi.h>
const char* ssid     = "HUB385-GUEST"; //your wifi router ssid
const char* password = "guestHUB385"; //your wifi router pw

const char* host = "169.53.41.241"; 

char* user = "zjonke";
char* token = "OeBjs0roaSDizLCMqq38AaP7qZdo"; //your token (Zeno)
char* flowPath = "/zjonke/weather";

void selectUser(char* userName) {
  if (userName == "jpavlek") {
    user = "jpavlek";
    token = "ReP4q5xZsAcIrIXv58wLt5vQehd6HhhG"; //your token (Jakov) 
    flowPath = "/jpavlek/maior";
  }

  if (userName == "zjonke") {
    user = "zjonke";
    token = "OeBjs0roaSDizLCMqq38AaP7qZdo"; //your token (Zeno)  
    flowPath = "/zjonke/weather";
  }
}

void sendDrop(int temperature, int humidity)
{
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
    if (client.connected()) {
        Serial.println("connection successful");

        client.print("POST /v0.1/"); client.print(user), client.println("/drop HTTP/1.1");
        //client.println("POST /v0.1/zjonke/drop HTTP/1.1");
        client.println("Host: api.flowthings.io");
        client.println("Connection: close");
        client.print("X-Auth-Token: ");
        client.println(token);
        client.println("Content-Type: application/json");
        String data = "{\"path\":\"" + String(flowPath) + "\",\"elems\":{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}}";

        client.print("Content-Length: ");
        client.println(data.length());

        client.println();

        client.println(data);

        while (client.available()) {
            char c = client.read();
            //Serial.print(c);
        }
        
    } else {
        Serial.println("connection failed");
        client.stop();
    }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  //selectUser("jpavlek");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
}

void loop() { 
  if (Serial.available()>0) {
    int command = Serial.read();
    delay(10);
    int valueTemperature = Serial.read();
    Serial.println(command);
    Serial.println(valueTemperature);
    if (command == 'A') {
      sendDrop(valueTemperature, 0);         
    }
    //Other data sources
    /*
     if (command == 'B') {
      sendDrop(valueTemperature, 0);         
    }
    */
  }
}
