//
// Created by bartek on 1/17/26.
//

#include "LcdPublisher.hpp"
#include <Wire.h>

LcdPublisher::LcdPublisher(const byte i2cAddr, const byte sda, const byte scl)
{
    // Initialize I2C with custom pins
    Wire.begin(sda, scl);

    // Create LCD instance (2x16 display)
    lcd = new LiquidCrystal_I2C(i2cAddr, 16, 2);

    // Initialize the LCD
    lcd->init();
    lcd->backlight();
    lcd->clear();
}

void LcdPublisher::publish(const std::string& str)
{
    if (lcd == nullptr) return;

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

void LcdPublisher::publish(const JsonDocument& json)
{
    if (lcd == nullptr) return;

    lcd->clear();

    // Extract key data from JSON and display on LCD
    // Row 0: First key-value pair or message
    // Row 1: Second key-value pair or additional info

    int row = 0;
    auto obj = json.as<JsonObjectConst>();
    for (JsonPairConst kv : obj) {
        if (row >= 2) break; // Only 2 rows available

        lcd->setCursor(0, row);

        // Format: "Key: Value"
        String line = String(kv.key().c_str()) + ": ";

        // Handle different value types
        if (kv.value().is<float>() || kv.value().is<double>()) {
            line += String(kv.value().as<float>(), 1);
        } else if (kv.value().is<int>()) {
            line += String(kv.value().as<int>());
        } else if (kv.value().is<const char*>()) {
            line += String(kv.value().as<const char*>());
        } else if (kv.value().is<bool>()) {
            line += kv.value().as<bool>() ? "true" : "false";
        }

        // Truncate to 16 characters
        if (line.length() > 16) {
            line = line.substring(0, 16);
        }

        lcd->print(line);
        row++;
    }
}
