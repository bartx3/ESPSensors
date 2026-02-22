//
// Created by bartek on 1/17/26.
//

#include "publishers/WifiPublisher.hpp"
#include <WiFi.h>

namespace utils {

WifiPublisher::WifiPublisher(const std::string &ssid,
                             const std::string &password,
                             const std::string &id,
                             const std::string &host, const uint16_t port)
    : id(id), m_host(host), m_port(port) {
  // Connect to WiFi
  WiFi.begin(ssid.c_str(), password.c_str());

  // Wait for connection
  int attempts = 0;
  while (WiFiClass::status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    attempts++;
  }
}

void WifiPublisher::publish(const std::string &str) {
  if (WiFiClass::status() != WL_CONNECTED) {
    return;
  }

  WiFiClient client;

  const std::string to_send = "[" + id + "] " + str;

  // Connect to TCP server
  if (client.connect(m_host.c_str(), m_port)) {
    // Send data
    client.print(to_send.c_str());
    client.flush();

    // Close connection
    client.stop();
  }
}

void WifiPublisher::publish(const JsonDocument &json) {
  if (WiFiClass::status() != WL_CONNECTED) {
    return;
  }

  WiFiClient client;

  auto to_send = json;
  to_send["id"] = id;
  // Connect to TCP server
  if (client.connect(m_host.c_str(), m_port)) {
    // Serialize JSON to string
    String jsonString;
    serializeJson(to_send, jsonString);

    // Send data
    client.print(jsonString);
    client.flush();

    // Close connection
    client.stop();
  }
}

} // namespace utils
