#include <WebSocketsServer.h>
#include "socket_server.h"
#include "sensors.h"

WebSocketsServer webSocket = WebSocketsServer(81);


  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("websocket server started on port 81");

webSocket.broadcastTXT('#');

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            {   
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
                // send message to server when Connected
                webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
            webSocket.sendTXT(num, payload);
            Serial.printf("[%u] get Text: %s\n", num, payload);

      // send message to server
      // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary lenght: %u\n", length);

            // send data to server
            // webSocket.sendBIN(payload, lenght);
            break;
    }
}
