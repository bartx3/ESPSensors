#include <Arduino.h>
#include <unity.h>

#include <ArduinoJson.h>

#include "sensors/SensorReader.hpp"

namespace {

class IntReader : public utils::SensorReader<int> {
public:
  IntReader(const std::string &name, int value)
      : utils::SensorReader<int>(name), value(value) {}

  int get_value() override { return value; }

private:
  int value;
};

class FloatReader : public utils::SensorReader<float> {
public:
  FloatReader(const std::string &name, float value)
      : utils::SensorReader<float>(name), value(value) {}

  float get_value() override { return value; }

private:
  float value;
};

} // namespace

void test_adds_single_value_to_json() {
  JsonDocument doc;
  auto obj = doc.to<JsonObject>();

  IntReader reader("Air Quality", 123);
  reader.addToJson(obj);

  TEST_ASSERT_TRUE(obj.containsKey("Air Quality"));
  TEST_ASSERT_EQUAL(123, obj["Air Quality"].as<int>());
}

void test_adds_multiple_values_to_json() {
  JsonDocument doc;
  auto obj = doc.to<JsonObject>();

  IntReader air("Air Quality", 200);
  IntReader smoke("Smoke", 55);

  air.addToJson(obj);
  smoke.addToJson(obj);

  TEST_ASSERT_EQUAL(200, obj["Air Quality"].as<int>());
  TEST_ASSERT_EQUAL(55, obj["Smoke"].as<int>());
}

void test_adds_float_values_to_json() {
  JsonDocument doc;
  auto obj = doc.to<JsonObject>();

  FloatReader temp("Temperature", 23.5f);
  temp.addToJson(obj);

  TEST_ASSERT_FLOAT_WITHIN(0.01f, 23.5f, obj["Temperature"].as<float>());
}

void test_add_to_json_via_interface() {
  JsonDocument doc;
  auto obj = doc.to<JsonObject>();

  utils::ISensorReader *reader = new IntReader("CO", 77);
  reader->addToJson(obj);

  TEST_ASSERT_EQUAL(77, obj["CO"].as<int>());

  delete reader;
}

void setup() {
  UNITY_BEGIN();

  RUN_TEST(test_adds_single_value_to_json);
  RUN_TEST(test_adds_multiple_values_to_json);
  RUN_TEST(test_adds_float_values_to_json);
  RUN_TEST(test_add_to_json_via_interface);

  UNITY_END();
}

void loop() {}
