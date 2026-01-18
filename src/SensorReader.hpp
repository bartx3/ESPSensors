//
// Created by bartek on 1/18/26.
//

#pragma once

#include <ArduinoJson.h>

class ISensorReader
{
public:
    virtual ~ISensorReader() = default;
    virtual void addToJson(JsonObject& obj) = 0;
protected:
    explicit ISensorReader(const std::string& name) : name(name) {};
    std::string name;
};

template <typename T>
class SensorReader : public ISensorReader
{
public:
    virtual T get_value() = 0;
    void addToJson(JsonObject& obj) override
    {
        obj[name] = get_value();
    }
protected:
    explicit SensorReader(const std::string& name) : ISensorReader(name) {}
};