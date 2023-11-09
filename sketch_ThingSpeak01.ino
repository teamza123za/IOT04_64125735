#include <ESP8266WiFi.h>
<<<<<<< HEAD
#include "ThingSpeak.h"
#include <DHT.h>

const char* ssid = "iPhone ของ Bank";
const char* password = "11111111";

unsigned long channelID = 2336982;
const char* writeKey = "SMNB0W6BV560NICV";

unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

WiFiClient client;
=======
#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "iPhone ของ Bank";
const char* password = "11111111";
const char* serverAddress = "http://172.20.10.3:3000/sensor";
>>>>>>> 140ac495d06a5ba52b5672a84db3982e9add197d

WiFiClient client;
HTTPClient http;
DHT dht(D4, DHT11);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
<<<<<<< HEAD
  ThingSpeak.begin(client);
=======
  WiFi.begin(ssid, password);
>>>>>>> 140ac495d06a5ba52b5672a84db3982e9add197d
  dht.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
<<<<<<< HEAD
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.println("\nConnected.");
    }

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
   
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);

      int x = ThingSpeak.writeFields(channelID, writeKey);
      if (x == 200) {
        Serial.println("Channel update successful.");
      } else {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
      }
    } else {
      Serial.println("Failed to read data from the sensor.");
    }

=======
  static unsigned long lastTime = 0;
  unsigned long timerDelay = 15000;
  if ((millis() - lastTime) > timerDelay) {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor");
    } else {
      Serial.print("Humidity: ");
      Serial.println(humidity);
      Serial.print("Temperature: ");
      Serial.println(temperature);

      DynamicJsonDocument jsonDocument(200);
      jsonDocument["hum"] = humidity;
      jsonDocument["temp"] = temperature;
      jsonDocument["timestamp"] = millis();

      String jsonData;
      serializeJson(jsonDocument, jsonData);

      http.begin(client, serverAddress);
      http.addHeader("Content-Type", "application/json");
      http.setTimeout(10000);

      int httpResponseCode = http.POST(jsonData);

      if (httpResponseCode > 0) {
        Serial.println("HTTP Response code: " + String(httpResponseCode));
      } else {
        Serial.println("Error on sending POST: " + String(httpResponseCode));
      }
      http.end();
    }
>>>>>>> 140ac495d06a5ba52b5672a84db3982e9add197d
    lastTime = millis();
  }
}
