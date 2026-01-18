//
// Created by bartek on 1/18/26.
//

#pragma once

#include "SensorReader.hpp"

namespace utils {

class MQReader : public SensorReader<int> {
public:
  MQReader(const std::string &name, byte pin);
  int get_value() override;

protected:
  const byte pin;
};

} // namespace utils