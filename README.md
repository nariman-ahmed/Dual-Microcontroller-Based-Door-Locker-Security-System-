# Dual Microcontroller-Based Door Locker Security System Using Password Authentication - ATmega32

## 📌 Project Overview
This project implements a **secure and efficient smart door control system** using two ATmega32 microcontrollers: 
1. **HMI_ECU** (Human-Machine Interface) for user interaction.
2. **Control_ECU** for password authentication and door control.

The two microcontrollers communicate via **UART**, and the system integrates various hardware components to enhance security and functionality.

## 🎯 Objective
The goal is to develop a **password-protected door locking system** that offers:
- **Reliable password authentication** stored in external EEPROM.
- **Real-time security alerts** using a PIR sensor and buzzer.
- **Secure motorized door control** via an H-bridge circuit.
- **User-friendly interface** with an LCD and keypad for password input.

## 🔑 Features
✔ **Password Protection** – Users can set and verify passwords securely stored in external EEPROM. 

✔ **LCD & Keypad Interface** – Easy interaction for entering and managing passwords.

✔ **UART Communication** – Data transfer between **HMI_ECU** and **Control_ECU**.

✔ **Motorized Door Control** – Uses an **H-bridge** to unlock/lock the door.

✔ **Buzzer Alert** – Triggers on failed password attempts and alerts.

✔ **PIR Motion Sensor** – Detects motion to trigger door operations.

✔ **Password Change Option** – Allows users to modify passwords after verification.

✔ **Security Lock** – Locks system for 1 minute after 3 incorrect password attempts.


## 🛠 Hardware Components
### **HMI_ECU Connections:**
- **LCD** (8-bit mode) for user display.
- **Keypad** (4x4) for password entry.
- **UART Communication** to connect with Control_ECU.

### **Control_ECU Connections:**
- **External EEPROM** (I2C Communication) for password storage.
- **Buzzer** for security alerts.
- **H-bridge Motor Driver** to control the motor.
- **Motor** for door locking/unlocking.
- **PIR Motion Sensor** for detecting movement.

## ⚙️ System Requirements
- **Microcontroller:** ATmega32 (both ECUs)
- **System Frequency:** 8 MHz
- **Software:** Embedded C, AVR Studio/Atmel Studio
- **Communication Protocols:** UART (between ECUs), I2C (EEPROM)

## 📽 Demo
🎥 **Watch the system in action:** [Demo Video Link](#)

## 🚀 Future Improvements
🔹 **Biometric Authentication** – Fingerprint or facial recognition for enhanced security.
🔹 **Remote Access Control** – Control the door via a mobile app.
🔹 **RFID/NFC Integration** – Enable keyless entry.
🔹 **Cloud-Based Monitoring** – Store logs of access attempts.

