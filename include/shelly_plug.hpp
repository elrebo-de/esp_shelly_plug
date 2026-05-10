/*
 * shelly_plug.hpp
 *
 *  Created on: 30.10.2025
 *      Author: christophoberle
 *
 * this work is licenced under the Apache 2.0 licence
 */

#ifndef SHELLY_PLUG_HPP_
#define SHELLY_PLUG_HPP_

#include <stdio.h>

#include <cstdint>
#include <string>

#include "HTTPClient.h"

class ShellyPlug {
public:
	ShellyPlug(std::string tag, std::string ipAddr);
	ShellyPlug(std::string tag, std::string ipAddr, bool initialState);
	virtual ~ShellyPlug();
    void Toggle();
    void Switch(bool switchState);
    void Switch(bool switchState, uint16_t toggleAfter);
    std::string ReadResponse();
    int GetLastHttpCode();

private:	
    std::string tag = "ShellyPlug";
	bool switchState; // the switch state of the shelly plug
	std::string ipAddr;
	HTTPClient *shellyPlug;

    int httpCode;
};

#endif /* SHELLY_PLUG_HPP_ */
