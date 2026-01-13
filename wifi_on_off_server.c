#include <ESP8266WiFi.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Relay pin
#define RELAY D1

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  // ON
  if (request.indexOf("/on") != -1) {
    digitalWrite(RELAY, HIGH);
  }

  // OFF
  if (request.indexOf("/off") != -1) {
    digitalWrite(RELAY, LOW);
  }

  // Web page
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<html><body>");
  client.println("<h1>WiFi ON/OFF Control</h1>");
  client.println("<a href=\"/on\"><button>ON</button></a>");
  client.println("<a href=\"/off\"><button>OFF</button></a>");
  client.println("</body></html>");

  delay(1);
}
