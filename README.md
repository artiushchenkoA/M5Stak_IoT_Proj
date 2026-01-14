# M5Stak_IoT_Proj
Semestral project for BI-IOT course at FIT CTU
# Distributed IoT Monitoring System (M5Stack)

## 1. Overview
This project demonstrates a distributed IoT architecture using two M5Stack Fire modules to monitor environmental data and implement a remote-control feedback loop. It fulfills the requirements for real-time sensor data acquisition, MQTT-based communication, and cloud-based data persistence.

## 2. Architecture & Logic
- **Sensor Node:** Collects data from a PIR Motion Sensor and a Hall Effect Sensor. It operates on a dynamic sampling frequency.
- **Gateway:** Acts as an intelligent controller. It monitors the PIR data; if motion is detected, it commands the Node to switch to "High-Frequency Mode" (100ms). Otherwise, it remains in "Power-Save Mode" (2000ms).
- **Data Persistence:** All telemetry is uploaded to InfluxDB Cloud using secure SSL/TLS protocols.

## 3. Hardware Connections
- **PIR Sensor (A):** Connected to **Port C** (Blue), GPIO 16.
- **Hall Sensor (B):** Connected to **Port B** (Black), GPIO 36 (Analog-capable).

## 4. Key Features
- **Non-blocking Loop:** Uses `millis()` timers to ensure MQTT messages are processed without delay.
- **Object-Oriented Sensors:** Abstracted sensor classes allow for easy hardware swapping.
- **Dynamic Reconfiguration:** Topic names and sampling rates can be changed via MQTT or physical buttons on the Gateway.

## 5. Test Scenarios
1. **Startup:** Both screens display connection status (WiFi/MQTT/Influx).
2. **Control Loop:** Wave a hand near the PIR sensor; observe the "Freq" value on the Node LCD drop to 100ms.
3. **Cloud Verification:** Check InfluxDB Data Explorer for the `measurements` bucket to see real-time graphs.
