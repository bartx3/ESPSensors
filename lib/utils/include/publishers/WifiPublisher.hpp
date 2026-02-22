//
// Created by bartek on 1/17/26.
//

#pragma once

#include "Publisher.hpp"

namespace utils {

class WifiPublisher : public Publisher {
public:
  WifiPublisher(const std::string &ssid, const std::string &password, const std::string &id,
                const std::string &host, uint16_t port);
  void publish(const std::string &str) override;
  void publish(const JsonDocument &json) override;

private:
  const  std::string id;
  std::string m_host;
  uint16_t m_port;
};

} // namespace utils
