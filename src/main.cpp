#include <Arduino.h>

#include <memory>
#include <set>

#include "LcdPublisher.hpp"
#include "MqReader.hpp"
#include "SensorReader.hpp"
#include "WifiPublisher.hpp"

#include "../credentials.hpp"

std::set<std::unique_ptr<Publisher>> publishers;
std::set<std::unique_ptr<ISensorReader>> sensors;

void setup() {
  auto LCD = new LcdPublisher(0x27, 21, 22);
  publishers.emplace(LCD);
  publishers.emplace(new WifiPublisher(SSID, PASSWORD, HOST, PORT));

  sensors.emplace(new MQReader("Air Quality", 13));
  LCD->publish("Warming up MQ sensors");
  delay(10000);
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