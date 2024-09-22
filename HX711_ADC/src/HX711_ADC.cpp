#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "HX711_ADC.h"

// static const char *TAG = "HX711_ADC";

HX711_ADC::HX711_ADC(gpio_num_t doutPin, gpio_num_t sckPin) {
    this -> doutPin = doutPin;
    this -> sckPin = sckPin;
}

void HX711_ADC::setGain(uint8_t gain) {
    if (gain < 64) GAIN = 2;  // 32, canal B
    else if (gain < 128) GAIN = 3;  // 64, canal A
    else GAIN = 1;  // 128, canal A
}

void HX711_ADC::begin() {
    gpio_set_direction(sckPin, GPIO_MODE_OUTPUT);
    gpio_set_direction(doutPin, GPIO_MODE_INPUT);
    setGain(128);
    powerUp();
}