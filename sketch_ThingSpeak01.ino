#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ชื่อ WiFi";
const char* password = "รหัส WiFi";

DHT dht(D4, DHT11);

const char* serverAddress = "http://172.20.10.4:3000/sensors";  // ที่อยู่ของเซิร์ฟเวอร์ของคุณ

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    StaticJsonDocument<200> doc;
    doc["humidity"] = humidity;
    doc["temperature"] = temperature;
    doc["timestamp"] = millis();

    String jsonData;
    serializeJson(doc, jsonData);

    HTTPClient http;
    http.begin(serverAddress);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode == 200) {
      Serial.println("Data sent successfully.");
    } else {
      Serial.print("Failed to send data. HTTP error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Failed to read data from the sensor.");
  }

  delay(15000);
}
