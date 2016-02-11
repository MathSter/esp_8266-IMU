#include <ESP8266WiFi.h>

//#include <WiFiManager.h>
#include <Ticker.h>
//#include <WebSocketsClient.h>

#include <ESP8266mDNS.h>

#include <Hash.h>

#include <Wire.h>
#include "sensors.h"
#include "socket_server.h"
#include "web_server.h"


const char* ssid = "******";
const char* pass = "******";
const char* host_name = "esp8266sd";

MDNSResponder mdns;
//WiFiManager wifiManager;

Ticker dac_timer;
bool measure = false;

sensors sensor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Wire.begin(0,2); // SDA: 0, SCL: 2 
  
  // WIFI
  WiFi.begin(ssid, pass);
  //wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {         // Wait for connection
    delay(500);
    Serial.print(".");
  }
  Serial.print("SSID : ");
  Serial.println(ssid);

  char result[16];
  sprintf(result, "%3d.%3d.%3d.%3d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  Serial.println();Serial.println(result);

  if (mdns.begin(host_name, WiFi.localIP())) {
    Serial.println("MDNS responder started");
    Serial.print("You can now connect to http://");
    Serial.print(host_name);
    Serial.println(".local");
  }

  // Add service to MDNS
  mdns.addService("http", "tcp", 80);
  mdns.addService("ws", "tcp", 81);

  // Start Webserver
  server.begin();
  Serial.println("HTTP web server started");

  // Start WebSocket server 


  // Setup Sensors 
  Serial.println("Initializing sensors");
  sensor.initialize();
  
  Serial.println("Verify sensors");
  sensor.verify();
  
  // Setup Ticker
  dac_timer.attach_ms(10,[](){measure = true})
}

int aquisition = 0;

void loop() {
  // put your main code here, to run repeatedly:
  webSocket.loop();
  server.handleClient();
  if(measure)
  {
    aquisition++;
    measure = false;
    measurements & measurment = sensor.getMeasurment();
    
  }
}
