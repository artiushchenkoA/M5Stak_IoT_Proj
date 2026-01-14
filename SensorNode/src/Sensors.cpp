#include "Sensors.h"

PIRSensor::PIRSensor(int p) : _p(p) {}
void PIRSensor::init() { 
    pinMode(_p, INPUT); 
}
int PIRSensor::getValue() { 
    return digitalRead(_p); 
}

HallSensor::HallSensor(int p) : _p(p) {}
void HallSensor::init() { 
    pinMode(_p, ANALOG); 
}
int HallSensor::getValue() { 
    return analogRead(_p); 
}