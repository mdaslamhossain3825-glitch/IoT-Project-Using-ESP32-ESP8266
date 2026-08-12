#include <WiFi.h>
#include <ThingESP.h>
#include <EEPROM.h>  // Include EEPROM library

ThingESP32 thing("Username", "ProjectName", "ProjectUserName");  //Enter "Username", "ProjectName", "ProjectUserName"

#define LED 5
#define EEPROM_SIZE 1  // Define EEPROM size to store one byte

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  // Initialize EEPROM with defined size
  EEPROM.begin(EEPROM_SIZE);

  // Retrieve the last saved LED state from EEPROM
  int lastState = EEPROM.read(0);
  digitalWrite(LED, lastState);  // Set the LED to the last state

  thing.SetWiFi("Enter Wi-fi Name", "Enter Wi-fi Password");
  thing.initDevice();
}

String HandleResponse(String query) {
  if (query == "on") {
    digitalWrite(LED, HIGH);
    EEPROM.write(0, HIGH);  // Save the state in EEPROM
    EEPROM.commit();        // Commit the changes to EEPROM
    return "LED Turned ON";
  }
  else if (query == "off") {
    digitalWrite(LED, LOW);
    EEPROM.write(0, LOW);  // Save the state in EEPROM
    EEPROM.commit();       // Commit the changes to EEPROM
    return "LED Turned OFF";
  }
  else if (query == "led status")
    return digitalRead(HIGH) ? "LED is ON" : "LED is OFF";
  else return "Your query was invalid..";
}

void loop() {
  thing.Handle();
}
