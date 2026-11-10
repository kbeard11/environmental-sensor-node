#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <SensirionI2cSht4x.h>
#include <BH1750.h>
#include <Adafruit_ADS1X15.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

const char* scriptURL =
  "YOUR_URL";

const char* firmware = "v1.1";

SensirionI2cSht4x sht4x;
BH1750 lightMeter;
Adafruit_ADS1015 ads;

void setup() {

  Serial.begin(115200);

  Wire.begin(5, 6);

  if (!ads.begin()) {

    Serial.println("ADS1015 not found");

    while (1) {
      delay(1000);
    }
  }

  sht4x.begin(Wire, 0x44);

  lightMeter.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 60) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi Connected");
    Serial.println(WiFi.localIP());

  } else {

    Serial.println("WiFi connection failed");
    Serial.println("Restarting in 5 minutes...");

    delay(300000);

    ESP.restart();
  }
}

void loop() {

  // Reconnect WiFi if needed
  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("WiFi disconnected");

    WiFi.disconnect(true);

    delay(1000);

    WiFi.begin(ssid, password);

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 60) {
      delay(500);
      Serial.print(".");
      attempts++;
    }

    Serial.println();

    if (WiFi.status() != WL_CONNECTED) {

      Serial.println("WiFi reconnect failed");
      Serial.println("Restarting ESP32");

      delay(5000);

      ESP.restart();
    }

    Serial.println("WiFi reconnected");
  }

  float temperature;
  float humidity;

  uint16_t error;
  char errorMessage[256];

  error = sht4x.measureHighPrecision(
    temperature,
    humidity);

  if (error) {

    errorToString(
      error,
      errorMessage,
      256);

    Serial.println(errorMessage);

    delay(5000);

    return;
  }

  float lux = lightMeter.readLightLevel();

  int16_t peperomia_sm =
    ads.readADC_SingleEnded(0);

  int16_t peperomia_v_sm =
    ads.readADC_SingleEnded(1);

  // Basic sanity checks
  if (temperature < -20 || temperature > 60) {
    Serial.println("Invalid temperature reading");
    return;
  }

  if (humidity < 0 || humidity > 100) {
    Serial.println("Invalid humidity reading");
    return;
  }

  if (lux < 0) {
    Serial.println("Invalid lux reading");
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Lux: ");
  Serial.println(lux);

  Serial.print("Peperomia_sm: ");
  Serial.println(peperomia_sm);

  Serial.print("Peperomia_v_sm: ");
  Serial.println(peperomia_v_sm);

  HTTPClient http;

  http.setTimeout(10000);

  http.begin(scriptURL);
  http.addHeader("Content-Type", "application/json");

  String payload =
    "{"
    "\"location\":\"office\","
    "\"node_id\":\"01\","
    "\"firmware\":\"" + String(firmware) + "\","
    "\"air_temp\":" + String(temperature, 2) + ","
    "\"humidity\":" + String(humidity, 2) + ","
    "\"lux\":" + String(lux, 2) + ","
    "\"peperomia_sm\":" + String(peperomia_sm) + ","
    "\"peperomia_v_sm\":" + String(peperomia_v_sm) + ","
    "\"batt_volt\":5.0"
    "}";

  int responseCode = http.POST(payload);

  Serial.print("HTTP Response: ");
  Serial.println(responseCode);

  if (responseCode <= 0) {

    Serial.println("Upload failed");
    http.end();

    delay(60000);

    ESP.restart();
  }

  String response = http.getString();

  Serial.print("Server Response: ");
  Serial.println(response);

  http.end();

  Serial.println("Waiting 15 minutes...");
  Serial.println();

  delay(900000);
}
