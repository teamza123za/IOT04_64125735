#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <DHT.h>

const char* ssid = "iPhone ของ Bank";
const char* password = "11111111";

unsigned long channelID = 2336982;
const char* writeKey = "SMNB0W6BV560NICV";

unsigned long lastTime = 0;
unsigned long timerDelay = 15000;

WiFiClient client;

DHT dht(D4, DHT11);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  dht.begin();
}

void loop() {
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

    lastTime = millis();
  }
}
