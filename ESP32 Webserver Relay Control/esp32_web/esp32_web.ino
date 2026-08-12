#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "AHS";
const char* password = "017937793";

// Set GPIO pin for the relay
const int relayPin = 5;

// Create an instance of the web server on port 80
WebServer server(80);

// Track the relay state
bool relayState = false;

void setup() {
  Serial.begin(115200);
  
  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Turn off the relay initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");

  // Print the ESP32 IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define the web server routes
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><style>";
  html += "body { display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }";
  html += "#relayButton { width: 200px; height: 100px; background-color: ";
  html += relayState ? "green" : "red";
  html += "; font-size: 20px; color: white; border: none; border-radius: 10px; }";
  html += "</style></head><body>";
  html += "<button id=\"relayButton\" onclick=\"toggleRelay()\">Relay ";
  html += relayState ? "ON" : "OFF";
  html += "</button>";
  html += "<script>";
  html += "function toggleRelay() {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/toggle', true);";
  html += "  xhr.onreadystatechange = function() {";
  html += "    if (xhr.readyState == 4 && xhr.status == 200) {";
  html += "      var relayButton = document.getElementById('relayButton');";
  html += "      if (xhr.responseText == 'ON') {";
  html += "        relayButton.style.backgroundColor = 'green';";
  html += "        relayButton.innerHTML = 'Relay ON';";
  html += "      } else {";
  html += "        relayButton.style.backgroundColor = 'red';";
  html += "        relayButton.innerHTML = 'Relay OFF';";
  html += "      }";
  html += "    }";
  html += "  };";
  html += "  xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleToggle() {
  relayState = !relayState;
  digitalWrite(relayPin, relayState ? HIGH : LOW);
  server.send(200, "text/plain", relayState ? "ON" : "OFF");
}
