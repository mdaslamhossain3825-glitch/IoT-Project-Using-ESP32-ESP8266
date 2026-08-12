#define BLYNK_PRINT Serial
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Replace with your template ID
#define BLYNK_TEMPLATE_ID "TMPL6RqCIVKIX"
#define BLYNK_TEMPLATE_NAME "Temperature Monitoring System"
#define BLYNK_AUTH_TOKEN "3ety3VFCnKyS1brVzhyb9PPrlQr65Pe3"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
// Define the DHT11 sensor type and the pin it's connected to
#define DHTTYPE DHT11
#define DHTPIN D4  // You can change this to the pin you're using

// Initialize the I2C LCD (change the address to your LCD's address if necessary)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AHS";
char pass[] = "017937793";

void setup() {
  // Debug console
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();

    // Display a startup message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  lcd.setCursor(4, 1);
  lcd.print("ASLAM YT");

  delay(3000);
}

void loop() {
  Blynk.run();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

    // Display the values on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" *C");

  Serial.println("Temperature: ");
  Serial.println(temperature);
  Serial.println(" °C, Humidity: ");
  Serial.println(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V0, temperature);

  delay(2000);  // Update every 2 seconds
}
