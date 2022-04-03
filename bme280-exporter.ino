#include <WiFi.h>
#include <M5Atom.h>
#include "./conf.hpp"

void print_mac_address(Stream & stream) {
  byte mac[6] {};
  WiFi.macAddress(mac);
  stream.print("MAC: ");
  stream.print(mac[5],HEX);
  stream.print(":");
  stream.print(mac[4],HEX);
  stream.print(":");
  stream.print(mac[3],HEX);
  stream.print(":");
  stream.print(mac[2],HEX);
  stream.print(":");
  stream.print(mac[1],HEX);
  stream.print(":");
  stream.println(mac[0],HEX);
}

void print_ip_address(Stream & stream) {
  const auto ip_address = WiFi.localIP();
  stream.println(ip_address);
}

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
}

void loop() {
}
