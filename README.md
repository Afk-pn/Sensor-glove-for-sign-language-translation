# Sensor Glove for Sign Language Translation

An Arduino-based wearable glove that recognizes predefined hand gestures using flex sensors and an MPU6050 IMU, then transmits the recognized gesture over Bluetooth to an Android application.

## System Overview

The glove captures finger-bending and hand-orientation data and performs real-time gesture classification on an Arduino Nano.

**System flow:**

Sensors → Arduino Nano → Gesture Classification → HC-05 Bluetooth → Android App

## Hardware

- Arduino Nano (ATmega328P)
- Flex sensors
- MPU6050 6-axis IMU
- HC-05 Bluetooth module
- Potentiometers
- Resistors and supporting circuitry

## Firmware

The firmware is written in Embedded C++ and includes:

- Analog sensor acquisition using Arduino ADC inputs
- Threshold-based finger-position detection
- MPU6050 interfacing over I²C
- Hand-orientation detection using accelerometer data
- Real-time gesture classification
- Serial/Bluetooth communication using HC-05
- Basic MPU6050 connection validation

## Recognized Gestures

The prototype recognizes 7 predefined gestures:

1. CALL ME
2. I LOVE YOU
3. GOOD LUCK
4. LOSER
5. ROCK ON
6. PAIN
7. HI

## Communication

Recognized gestures are transmitted through an HC-05 Bluetooth module to an Android application, where they are displayed as text and converted to speech.

## Project Structure

- `sensor glove.ino` — final Arduino firmware
