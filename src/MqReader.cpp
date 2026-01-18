//
// Created by bartek on 1/18/26.
//

#include "MqReader.hpp"

MQReader::MQReader(const std::string& name, const byte pin) : SensorReader(name), pin(pin) {}

float MQReader::get_value()
{
    return analogRead(pin);
}
