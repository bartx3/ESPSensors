//
// Created by bartek on 1/17/26.
//

#pragma once

#include "Publisher.hpp"
#include <LiquidCrystal_I2C.h>

class LcdPublisher : public Publisher {
public:
  LcdPublisher(byte i2cAddr, byte sda, byte scl);
  void publish(const std::string &str) override;
  void publish(const JsonDocument &json) override;

  LiquidCrystal_I2C *lcd = nullptr;
};