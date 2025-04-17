# 2021-25-MAP-G-43-Two-Way-People-Counter-with-Automatic-Lighting-Control

# IoT-Based Two Way People Counter with Automatic Lighting Control

This project uses ESP32, IR sensors, and ThingSpeak Cloud to count people entering/exiting a room and automatically control lighting. When the room is empty, the light turns off, saving power.

## 🔧 Hardware Components
- ESP32 WROOM-32
- 2x IR Sensors
- Relay Module
- 16x2 LCD (I2C)
- Power Supply (12V)
- LED bulb (for light simulation)

## 📦 Software Requirements
- Arduino IDE
- ESP32 Board Package
- Libraries: `LiquidCrystal_I2C`, `WiFi`, `HTTPClient`, `Wire`

## 🚀 Features
- Real-time visitor count
- Bidirectional sensing using 2 IR sensors
- Auto lighting using relay
- Cloud data logging on ThingSpeak
- LCD display of current room occupancy

## 📡 Cloud Integration
Uses [ThingSpeak](https://thingspeak.com/) for cloud monitoring.

## 📁 Directory Structure
