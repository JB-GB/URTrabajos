#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wifi";         // pendiente a confirmar
const char* password = "Password"; // pendiente a confirmacion

WebServer server(80);
void handleData() {
  String json = R"rawliteral({
    "velocidad": 55,
    "rpm": 4800,
    "temperatura_motor": 87,
    "marcha": "3",
    "neumaticos": {
      "frontal_izquierdo": 66,
      "frontal_derecho": 65,
      "trasero_izquierdo": 64,
      "trasero_derecho": 63
    }
  })rawliteral";
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP()); // La IP a usar
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}
