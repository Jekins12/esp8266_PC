
# ESP8266 PC Controller

This project is a simple ESP8266-based control system that enables toggling and forcing the shutdown of a PC via HTTP requests. The system offers discoverability features and provides device information, including the device name, IP address, and MAC address.

## Features
- **Discover Endpoint:** Returns device information, including the name, IP address, MAC address, and available endpoints.
- **Toggle State Endpoint:** Toggles the PC power by simulating a button press.
- **Force Off Endpoint:** Forces the PC to turn off by holding the button press for an extended period.

## Requirements
- ESP8266 microcontroller (e.g., NodeMCU)
- [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson) - Used for JSON formatting.
- A connected button or relay to simulate PC power button actions.

## Setup

1. **Hardware Setup:**
   - Connect the transistor to the ESP8266 pin specified as `buttonPin` (in this code, it is set to GPIO 5 or D1 on some boards).

2. **Wi-Fi Configuration:**
   - Set your Wi-Fi SSID and password in the `config.h` file.

3. **Endpoints:** The following HTTP endpoints are available:
   - `/discover`: Provides device details in JSON format.
   - `/toggle_state`: Toggles the PC power by simulating a short button press.
   - `/forceOff`: Holds the button press for a longer duration, forcing a shutdown.

## Usage
After powering on and connecting to Wi-Fi, the ESP8266 will serve an HTTP server at its IP address.

- **Discover Device:** Navigate to `http://<device_ip>/discover` to view the device information in JSON format.
- **Toggle State:** Navigate to `http://<device_ip>/toggle_state` to send a short button press signal.
- **Force Off:** Navigate to `http://<device_ip>/forceOff` to simulate a long button press for shutdown.

## Example Response for `/discover`
```json
{
  "name": "ESP8266 PC",
  "ip_address": "192.168.1.50",
  "mac_address": "XX:XX:XX:XX:XX:XX",
  "endpoints": ["/toggle_state", "/forceOff"]
}
```


## Acknowledgments
- The [ESP8266WebServer Library](https://github.com/esp8266/Arduino) for managing HTTP requests.
