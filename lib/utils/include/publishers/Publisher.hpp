//
// Created by bartek on 1/17/26.
//
#pragma once

#include <ArduinoJson.h>
#include <string>

namespace utils {

class Publisher {
public:
  virtual ~Publisher() = default;

  virtual void publish(const std::string &str);
  virtual void publish(const JsonDocument &json);
};

} // namespace utils