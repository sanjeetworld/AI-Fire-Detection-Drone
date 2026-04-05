# 🔥 Fire Detection and Rescue Drone 🚁

🚀 Smart drone system for **real-time fire detection**, **autonomous response**, and **location-based alerting** using computer vision and IoT technologies.

---

## 📌 Overview

This project presents an intelligent drone system capable of detecting fire using **computer vision and sensors**, processing data using **ESP32**, and triggering automated actions like **alert notifications** and **extinguisher deployment**.

It is designed for **disaster management, forest fire monitoring, and emergency response systems**.

---

## 🚀 Features

- 🔥 **Real-time fire detection** using flame, smoke, and temperature sensors  
- 🧠 **AI-based processing** using ESP32 and computer vision (OpenCV)  
- 📡 **GPS-based location tracking**  
- 📲 **GSM alerts (SMS/Call)** for emergency notification  
- ⚙️ **Automatic extinguisher activation** using servo motor  
- 🚁 **Drone integration** for aerial monitoring  
- 🧩 Modular and scalable system design  

---

## 🛠️ Tech Stack

### 💻 Software
- Python  
- OpenCV  
- NumPy  
- PySerial  

### 🔌 Hardware
- ESP32 Microcontroller  
- Flame Sensor  
- Smoke Sensor (MQ-2)  
- Temperature Sensor  
- Servo Motor  
- GSM Module (SIM800L / SIM900)  
- GPS Module (NEO-6M)  

### 🚁 Drone Components
- 1000KV BLDC Motors (×4)  
- 30A ESC (×4)  
- Propellers  
- KK2 Flight Controller  
- Lithium-ion Battery (22000 mAh)  
- FlySky Transmitter & Receiver  

---

## ⚙️ System Architecture


           ┌────────────────────────────┐
           │        INPUT LAYER         │
           │ Flame | Smoke | Temp Sensor│
           └────────────┬───────────────┘
                        ↓
           ┌────────────────────────────┐
           │     PROCESSING LAYER       │
           │        ESP32 Controller    │
           │ - Data Acquisition         │
           │ - Fire Detection Logic     │
           │ - Decision Making          │
           └───────┬─────────┬──────────┘
                   ↓         ↓
          ┌────────────┐  ┌────────────┐
          │   SERVO    │  │    GSM     │
          │ (Extinguish)│ │ (Alert SMS)│
          └────────────┘  └──────┬─────┘
                                  ↓
                            ┌──────────┐
                            │   GPS    │
                            │ Location │
                            └──────────┘

### 🔍 Working Flow

1. Sensors (flame, smoke, temperature) continuously monitor the environment.  
2. ESP32 processes sensor data and detects fire conditions.  
3. If fire is detected:  
   - Servo motor activates the extinguisher mechanism  
   - GSM module sends alert messages  
   - GPS module provides real-time location  
4. System ensures fast and automated emergency response.
