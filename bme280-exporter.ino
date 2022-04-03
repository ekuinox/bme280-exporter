#include <Wire.h>
#include <WiFi.h>
#include <M5Atom.h>
#include <BME280I2C.h>
#include "conf.hpp"
#include "metrics.hpp"
#include "bme280_metrics.hpp"

/**
 * @brief 受け取った Stream に MAC アドレスを出力する
 */
void print_mac_address(Stream & stream);

/**
 * @brief 受け取った Stream に IPv4 アドレスを出力する
 */
void print_ip_address(Stream & stream);

/**
 * @brief クライアントにレスポンスを返す
 */
void recv_client(WiFiClient & client);

WiFiServer server(80);
BME280I2C bme280 {};
constexpr uint32_t metrics_count = 3;
Metric* metrics[metrics_count] = {
  new TemperatureMetric(&bme280),
  new HumidityMetric(&bme280),
  new PressureMetric(&bme280),
};

void setup() {
  // Enable lcd and serial. Disable sdcard.
  M5.begin(true, false, true);
  delay(50);

  // connect wifi ap.
  WiFi.begin(WIFI_SSID, WIFI_PASSPHRASE);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Wait for WiFi connection ...");
  }
  Serial.println("Connected WiFi");
  print_mac_address(Serial);
  print_ip_address(Serial);

  // Setup pins
  pinMode(BME280_SCK_PIN, INPUT_PULLUP);
  pinMode(BME280_SDI_PIN, INPUT_PULLUP);

  // Start I2C
  Wire.begin(BME280_SDI_PIN, BME280_SCK_PIN);

  // Start BME280
  while (!bme280.begin()) {
    Serial.println("Wait for BME280 sensor!");
    delay(500);
  }

  Serial.println("Found BME280");
  if (bme280.chipModel() != BME280::ChipModel::ChipModel_BME280) {
    Serial.println("ChipModel is not BME280");
  }
    
  server.begin();
}

void loop() {
  auto client = server.available();
  recv_client(client);

  M5.update();
}

void print_mac_address(Stream & stream) {
  byte mac[6] {};
  WiFi.macAddress(mac);
  stream.print(mac[5], HEX);
  stream.print(":");
  stream.print(mac[4], HEX);
  stream.print(":");
  stream.print(mac[3], HEX);
  stream.print(":");
  stream.print(mac[2], HEX);
  stream.print(":");
  stream.print(mac[1], HEX);
  stream.print(":");
  stream.println(mac[0], HEX);
}

void print_ip_address(Stream & stream) {
  const auto ip_address = WiFi.localIP();
  stream.println(ip_address);
}

void recv_client(WiFiClient & client) {
  if (!client) {
    return;
  }
  Serial.println("new client!");
  while (client.connected()) {
    if (!client.available()) {
      continue;
    }
    const auto c = client.read();
    if (c != '\n') {
      continue;
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain");
    client.println();
    for (uint32_t i = 0; i < metrics_count; ++i) {
      metrics[i]->update_metric();
      metrics[i]->write_metric(client);
    }
    break;
  }
  client.stop();
  Serial.println("client closed");
}
