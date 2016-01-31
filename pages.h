
void returnOK() {
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "");
}

void returnFail(String msg) {
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void set_acc_settings() {
  returnOK();
}

void get_acc_settings() {
  server.send(200, "text/json", "");
  server.sendContent("[1,1,1]");
}

void handleNotFound() {
  server.send(404, "text/plain", "404 File not found\n");
}
