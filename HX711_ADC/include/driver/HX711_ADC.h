#ifndef HX711_ADC_h
#define HX711_ADC_h

#include <stdint.h>
#include <stdbool.h>
#include "driver/gpio.h"
#include "config.h"


#define DATA_SET  (SAMPLES + IGN_HIGH_SAMPLE + IGN_LOW_SAMPLE)

#if (SAMPLES != 1 && SAMPLES != 2 && SAMPLES != 4 && SAMPLES != 8 && SAMPLES != 16 && SAMPLES != 32 && SAMPLES != 64 && SAMPLES != 128)
    #error "Número de SAMPLES não é válido!"
#endif

#if (SAMPLES == 1 && (IGN_HIGH_SAMPLE != 0 || IGN_LOW_SAMPLE != 0))
    #error "Número de SAMPLES não é válido!"
#endif

#if (SAMPLES == 1)
    #define DIVB 0
#elif (SAMPLES == 2)
    #define DIVB 1
#elif (SAMPLES == 4)
    #define DIVB 2
#elif (SAMPLES == 8)
    #define DIVB 3
#elif (SAMPLES == 16)
    #define DIVB 4
#elif (SAMPLES == 32)
    #define DIVB 5
#elif (SAMPLES == 64)
    #define DIVB 6
#elif (SAMPLES == 128)
    #define DIVB 7
#endif

#define SIGNAL_TIMEOUT 100

class HX711_ADC {
public:
    HX711_ADC(gpio_num_t dout, gpio_num_t sck);
    void setGain(uint8_t gain);
    void begin();
    void begin(uint8_t gain);
    void start(unsigned long t);
    void start(unsigned long t, bool dotare);
    int startMultiple(unsigned long t);
    int startMultiple(unsigned long t, bool dotare);
    void tare();
    void tareNoDelay();
    bool getTareStatus();
    void setCalFactor(float cal);
    float getCalFactor();
    float getData();
    int getReadIndex();
    float getConversionTime();
    float getSPS();
    bool getTareTimeoutFlag();
    void disableTareTimeout();
    long getSettlingTime();
    void powerDown();
    void powerUp();
    long getTareOffset();
    void setTareOffset(long newoffset);
    uint8_t update();
    bool dataWaitingAsync();
    bool updateAsync();
    void setSamplesInUse(int samples);
    int getSamplesInUse();
    void resetSamplesIndex();
    bool refreshDataSet();
    bool getDataSetStatus();
    float getNewCalibration(float known_mass);
    bool getSignalTimeoutFlag();
    void setReverseOutput();

protected:
    void conversion24bit();
    long smoothedData();
    uint8_t sckPin;
    uint8_t doutPin;
    uint8_t GAIN;
    float calFactor= 1.0;
    float calFactorRecip= 1.0;
    volatile long dataSampleSet[DATA_SET + 1];
    long tareOffset = 0;
    int readIndex = 0;
    unsigned long conversionStartTime = 0;
    unsigned long conversionTime = 0;
    uint8_t isFirst = 1;
    uint8_t tareTimes = 0;
    uint8_t divBit = DIVB;
    const uint8_t divBitCompiled= DIVB;
    bool doTare = 0;
    bool startStatus = 0;
    unsigned long startMultipleTimeStamp = 0;
    unsigned long startMultipleWaitTime = 0;
    uint8_t convRslt = 0;
    bool tareStatus = 0;
    unsigned int tareTimeOut =  (SAMPLES + IGN_HIGH_SAMPLE + IGN_HIGH_SAMPLE) * 150;
    bool tareTimeoutFlag = 0;
    bool tareTimeoutDisable = 0;
    int samplesInUse = SAMPLES;
    long lastSmoothedData = 0;
    bool dataOutOfRange = 0;
    unsigned long lastDoutLowTime = 0;
    bool signalTimeoutFlag = 0;
    bool reverseVal = 0;
    bool dataWaiting = 0;
};

#endif

