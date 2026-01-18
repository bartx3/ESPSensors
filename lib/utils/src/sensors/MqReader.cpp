//
// Created by bartek on 1/18/26.
//

#include "MqReader.hpp"

namespace utils {

MQReader::MQReader(const std::string &name, const byte pin)
    : SensorReader(name), pin(pin) {
  pinMode(pin, INPUT);
}

int MQReader::get_value() { return analogRead(pin); }

} // namespace utils
