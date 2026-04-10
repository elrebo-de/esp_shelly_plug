# Shelly Plug component

This repository contains an ESP-IDF component for the Shelly Plug. It runs on
any ESP32 processor and is built using the ESP-IDF build system in version 5.5.0+.

The component is implemented as C++ class `ShellyPlug`.

It depends on ESP Component elrebo-de/http_client.

## Connecting the component

The constructor of class `ShellyPlug` has two parameters:

| Parameter    | Type of Parameter | Usage                             |
|:-------------|:------------------|:----------------------------------|
| tag          | std::string       | the tag to be used in the ESP log |
| ipAddr       | std::string       | the IP Address of the Shelly Plug |

Currently only an http connection to an IP address can be used.

# Usage

The Shelly Plug can be switched on/off with methods `Switch` and `Toggle` of class `ShellyPlug`.

The method `Switch` has two variants. One simply sets the new `switchState`, the second variant uses a second parameter 
`toggleAfter` which toggles back the switchState of the plug after the given nr of seconds.

The method `ReadResponse` returns the response of the last HTTP request, which was sent to the Shelly Plug, as a std::string.

## API
The API of the component is located in the include directory ```include/shelly_plug.hpp``` and defines the
C++ class ```ShellyPlug```

```C
class ShellyPlug {
public:
    ShellyPlug(std::string tag, std::string ipAddr);
    virtual ~ShellyPlug();
    void Toggle();
    void Switch(bool switchState);
    void Switch(bool switchState, uint16_t toggleAfter);
    std::string ReadResponse();

private:	
    std::string tag = "ShellyPlug";
    bool switchState; // the switch state of the shelly plug
    std::string ipAddr;
    HTTPClient *shellyPlug;
};
```

# License

This component is provided under the Apache 2.0 license.
