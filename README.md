# Wise Water System

This project is a water management system using ESP32, ultrasonic sensors, temperature sensors, turbidity sensors, and Firebase for data logging.

## Features
- **Real-time Water Flow Monitoring**: Tracks the flow rate and calculates total and daily water usage.
- **Turbidity Detection**: Measures the turbidity level to check water clarity and trigger appropriate actions.
- **Temperature Monitoring**: Monitors water temperature and uploads data to Firebase.
- **Firebase Integration**: Logs all data to Firebase for remote monitoring.

## Components
- **ESP32**: Main microcontroller for processing sensor data and handling WiFi.
- **Ultrasonic Sensors**: For measuring water level in main and small tanks.
- **Temperature Sensor (DS18B20)**: For monitoring water temperature.
- **Flow Sensor**: For measuring water flow rate.
- **Turbidity Sensor**: To determine water clarity.

## Requirements
- **Arduino IDE**
- **ESP32 Libraries**: [Ultrasonic](https://github.com/JRodrigoTech/Ultrasonic-HC-SR04), [OneWire](https://github.com/PaulStoffregen/OneWire), [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)
- **Firebase Realtime Database**

## Usage
1. Set up Firebase with a project and add your Firebase Host and Auth keys.
2. Connect the ESP32 to WiFi by updating the SSID and password in `main.cpp`.
3. Upload the code to ESP32.
4. Monitor data on Firebase and in the Serial Monitor.

## License
MIT License
