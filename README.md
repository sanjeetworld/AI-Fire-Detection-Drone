# Fire Detection and Rescue Drone

Smart drone system for real-time fire detection, autonomous response, and location-based alerting using computer vision and IoT technologies.

## Overview

This project presents an intelligent drone system capable of detecting fire using computer vision and sensors, processing data with an ESP32 microcontroller, and triggering automated actions such as alert notifications and extinguisher deployment.

It is designed for disaster management, forest fire monitoring, and emergency response systems.

## Features

- Real-time fire detection using flame, smoke, and temperature sensors
- AI-based processing with ESP32 and computer vision (OpenCV)
- GPS-based location tracking
- GSM alerts (SMS/Call) for emergency notification
- Automatic extinguisher activation using a servo motor
- Drone integration for aerial monitoring
- Modular and scalable system design

## Tech Stack

### Software

- Python
- OpenCV
- NumPy
- PySerial

### Hardware

- ESP32 Microcontroller
- Flame Sensor
- Smoke Sensor (MQ-2)
- Temperature Sensor
- Servo Motor
- GSM Module (SIM800L / SIM900)
- GPS Module (NEO-6M)

### Drone Components

- 1000KV BLDC Motors (×4)
- 30A ESC (×4)
- Propellers
- KK2 Flight Controller
- Lithium-ion Battery (22000 mAh)
- FlySky Transmitter & Receiver

## System Architecture

```mermaid
flowchart TD

    A[🔥 Fire Environment] --> B[Input Layer]

    B --> B1[Flame Sensor]
    B --> B2[Smoke Sensor<br/>MQ-2]
    B --> B3[Temperature Sensor]

    B1 --> C[ESP32 Controller]
    B2 --> C
    B3 --> C

    D[GPS Module<br/>NEO-6M] --> C

    C --> C1[Data Acquisition]
    C --> C2[Fire Detection Logic]
    C --> C3[Decision Making]

    C3 --> E[Servo Motor]
    E --> E1[🔥 Extinguisher Activation]

    C3 --> F[GSM Module<br/>SIM800L / SIM900]
    F --> F1[📱 Emergency SMS / Call]

    C --> G[Drone Platform]
    G --> G1[Flight Controller]
    G --> G2[BLDC Motors + ESC]
    G --> G3[Aerial Monitoring]

    D --> H[📍 Fire Location]
    H --> F

    style A fill:#ff6b35,color:#fff
    style C fill:#2563eb,color:#fff
    style E fill:#dc2626,color:#fff
    style F fill:#16a34a,color:#fff
    style D fill:#9333ea,color:#fff
    style G fill:#0891b2,color:#fff
