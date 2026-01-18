//
// Created by bartek on 1/18/26.
//

#pragma once

#include "SensorReader.hpp"

class MQReader : public SensorReader<float> {
public:
  MQReader(const std::string &name, byte pin);
  float get_value() override;

protected:
  const byte pin;
};