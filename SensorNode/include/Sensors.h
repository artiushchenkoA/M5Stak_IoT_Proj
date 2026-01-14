// Header file for Sensor Abstraction: defines the interface for different hardware sensors.

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

// Abstract base class to provide a unified interface for all sensor types.
class SensorDevice {
public:
    virtual void init() = 0;
    virtual int getValue() = 0;
};

// PIR Sensor class for motion detection.
class PIRSensor : public SensorDevice {
private:
    int _p;
public:
    PIRSensor(int p);
    // Function init ensures the GPIO pin is set to input mode.
    void init() override;
    // Function getValue reads digital state (0 or 1). @return motion status.
    int getValue() override;
};

// Hall Sensor class for magnetic field measurement.
class HallSensor : public SensorDevice {
private:
    int _p;
public:
    HallSensor(int p);
    // Function init ensures the GPIO pin is set to analog mode.
    void init() override;
    // Function getValue reads magnetic intensity. @return analog value (0-4095).
    int getValue() override;
};

#endif