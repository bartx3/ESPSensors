#include <Arduino.h>

#include <memory>
#include <set>

#include "publishers/LcdPublisher.hpp"
#include "publishers/WifiPublisher.hpp"
#include "sensors/MqReader.hpp"

#include "../credentials.hpp"

std::set<std::unique_ptr<utils::Publisher>> publishers;
std::set<std::unique_ptr<utils::ISensorReader>> sensors;

void setup() {
  // auto LCD = new utils::LcdPublisher(0x27, 21, 22);
  // publishers.emplace(LCD);
  publishers.emplace(new utils::WifiPublisher(SSID, PASSWORD, MY_ID, HOST, PORT));

  sensors.emplace(new utils::MQReader("Carbon Monoxide", 0));
  // LCD->publish("Warming up MQ sensors");
  delay(10000);  // Allow sensors to stabilize
}

void loop() {
  JsonDocument doc;
  auto obj = doc.to<JsonObject>();

  for (auto &sensor : sensors) {
    sensor->addToJson(obj);
  }

  for (auto &pub : publishers) {
    pub->publish(doc);
  }
  delay(1000);
}