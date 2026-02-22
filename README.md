# Furnace Monitor

**Keywords:** ESP32, IoT, monitoring, furnace, embedded systems

## What is it?
This is a simple project utilizing ESP32 WROOM board, together with MQ sensors and LCD display. It reads input from all given sensors and publishes it using available channels including LCD display and a server.

## Getting Started
### Wifi settings
In order to connect to a server, the user must input WiFi credentials as well as host name and port. Due to the lack of a proper input devices and time consumption those values are hard-coded and should be disclosed in an unversioned header file for example `credentials.hpp` in the main project directory. Example contents of `credentials.hpp`:
```
#pragma once

#define SSID "ssid"
#define PASSWORD "1234"
#define MY_ID "ID"
#define HOST "192.168.1.100"
#define PORT 8080
```

### Message format
All messages to server are being sent in a JSON format `{<sensor name>: <sensor value>}`.

## Unit tests
In order to run unit tests, the user must have PlatformIO installed. After cloning the repository, navigate to the main project directory and run:
```pio test -v
```