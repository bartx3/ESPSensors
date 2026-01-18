//
// Created by bartek on 1/17/26.
//

#include "LcdPublisher.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <Wire.h>

namespace utils {

LcdPublisher::LcdPublisher(const byte i2cAddr, const byte sda, const byte scl) {
  // Initialize I2C with custom pins
  Wire.begin(sda, scl);

  // Create LCD instance (2x16 display)
  lcd = new LiquidCrystal_I2C(i2cAddr, 16, 2);

  // Initialize the LCD
  lcd->init();
  lcd->backlight();
  lcd->clear();
}

void LcdPublisher::publish(const std::string &str) {
  if (lcd == nullptr)
    return;

  lcd->clear();
  lcd->setCursor(0, 0);

  // For 2x16 display, split string across two rows
  if (str.length() <= 16) {
    // Fits on one row
    lcd->print(str.c_str());
  } else {
    // Split across two rows
    lcd->print(str.substr(0, 16).c_str());
    lcd->setCursor(0, 1);
    lcd->print(str.substr(16, 16).c_str());
  }
}

void LcdPublisher::publish(const JsonDocument &json) {
  if (lcd == nullptr)
    return;

  lcd->clear();

  // Extract key data from JSON and display on LCD
  // Row 0: First key-value pair or message
  // Row 1: Second key-value pair or additional info

  std::string headers;
  std::string values;
  auto obj = json.as<JsonObjectConst>();
  for (JsonPairConst kv : obj) {
    std::string header;
    std::string key = kv.key().c_str();
    for (auto &ch : key) {
      if (not std::isspace(ch) and ch == toUpperCase(ch)) {
        header += ch;
      }
    }
    std::stringstream stream;
    stream << std::setprecision(2) << kv.value().as<std::string>();
    std::string value = stream.str();

    header += " ";
    value += " ";
    if (header.length() < value.length()) {
      header += std::string(value.length() - header.length(), ' ');
    } else {
      value += std::string(header.length() - value.length(), ' ');
    }
    headers += header;
    values += value;
  }

  lcd->setCursor(0, 0);
  lcd->print(headers.c_str());
  lcd->setCursor(0, 1);
  lcd->print(values.c_str());
}

} // namespace utils