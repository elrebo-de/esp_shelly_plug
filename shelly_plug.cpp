/*
 * ShellyPlug.cpp
 *
 *  Created on 01.11.2025
 *      Author: christophoberle
 *
 * this work is licenced under the Apache 2.0 licence
 */

#include "shelly_plug.hpp"
#include "esp_log.h"

ShellyPlug::ShellyPlug(std::string tag, std::string ipAddr) : ShellyPlug(tag, ipAddr, false) {}

ShellyPlug::ShellyPlug(std::string tag, std::string ipAddr, bool initialState) {
	this->tag = tag;
    this->ipAddr = ipAddr;

    // set switchState to initialState
    this->switchState = initialState;

    // initialize ShellyPlug HTTPClient
    this->shellyPlug = new HTTPClient();

    // switch shelly plug to initialState
    std::string command = "http://";
    command += this->ipAddr;
    command += "/rpc/Switch.Set?id=0&on=";
    command += (initialState ? "true" : "false");

    ESP_LOGI(this->tag.c_str(), "ShellyPlug Command: %s", command.c_str());

    this->shellyPlug->begin(command.c_str());
    this->httpCode = this->shellyPlug->GET();
    if (this->httpCode > 0)
    {
        ESP_LOGI(this->tag.c_str(), "HTTP GET code: %d", this->httpCode);
        if (this->httpCode == HTTP_CODE_OK)
        {
            ESP_LOGI(this->tag.c_str(), "HTTP GET successful.");
        }
    }
    else
    {
        ESP_LOGE(this->tag.c_str(), "HTTP GET failed, error: %s", HTTPClient::errorToString(this->httpCode).c_str());
    }
}

ShellyPlug::~ShellyPlug() {
}

void ShellyPlug::Switch(bool switchState) {
	this->switchState = switchState;

    // switch shelly plug
    std::string command = "http://";
    command += this->ipAddr;
    command += "/rpc/Switch.Set?id=0&on=";
    command += this->switchState ? "true" : "false";

    ESP_LOGI(this->tag.c_str(), "ShellyPlug Command: %s", command.c_str());

    this->shellyPlug->setURL(command.c_str());
    this->httpCode = this->shellyPlug->GET();
    if (this->httpCode > 0)
    {
        ESP_LOGI(this->tag.c_str(), "HTTP GET code: %d", this->httpCode);
        if (this->httpCode == HTTP_CODE_OK)
        {
            ESP_LOGI(this->tag.c_str(), "HTTP GET successful.");
        }
    }
    else
    {
        ESP_LOGE(this->tag.c_str(), "HTTP GET failed, error: %s", HTTPClient::errorToString(this->httpCode).c_str());
    }
}

void ShellyPlug::Switch(bool switchState, uint16_t toggleAfter) {
	this->switchState = switchState;

    // switch shelly plug
    std::string command = "http://";
    command += this->ipAddr;
    command += "/rpc/Switch.Set?id=0&on=";
    command += this->switchState ? "true" : "false";
    command += "&toggle_after=";
    command += std::to_string(toggleAfter);

    ESP_LOGI(this->tag.c_str(), "ShellyPlug Command: %s", command.c_str());

    this->shellyPlug->setURL(command.c_str());
    this->httpCode = this->shellyPlug->GET();
    if (this->httpCode > 0)
    {
        ESP_LOGI(this->tag.c_str(), "HTTP GET code: %d", this->httpCode);
        if (this->httpCode == HTTP_CODE_OK)
        {
            ESP_LOGI(this->tag.c_str(), "HTTP GET successful.");
        }
    }
    else
    {
        ESP_LOGE(this->tag.c_str(), "HTTP GET failed, error: %s", HTTPClient::errorToString(this->httpCode).c_str());
    }
}

std::string ShellyPlug::ReadResponse() {
    std::string payload = "";
    if (this->shellyPlug->available() > 0 || this->shellyPlug->connected())
    {
        payload = std::string(this->shellyPlug->readString().c_str());
    }
    return payload;
}

void ShellyPlug::Toggle() {
    this->Switch(!this->switchState);
}

int ShellyPlug::GetLastHttpCode() {
    return this->httpCode;
}

