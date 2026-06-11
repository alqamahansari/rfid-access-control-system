# RFID-Based Timed Access Control System

## Overview

This project is an RFID-based access control and appliance automation system developed using Arduino Nano. The system authenticates RFID cards and controls a relay-connected appliance (TV in this demonstration) for predefined durations. Each RFID card can be used only once until an administrator reset card is scanned.

The project demonstrates RFID authentication, access control, relay switching, OLED-based user feedback, and state management in embedded systems.


## Features

### RFID Authentication

* Reads RFID card UIDs using the MFRC522 RFID module.
* Allows access only to registered RFID cards.

### One-Time Use Cards

* Card 1 activates the appliance for 20 seconds.
* Card 2 activates the appliance for 40 seconds.
* Each card becomes unavailable after use.

### Reset Card

* Administrator RFID tag resets the system.
* Restores access privileges for all user cards.

### Appliance Control

* Relay module controls an external appliance.
* LED indicator simulates room lighting during operation.

### OLED Display Interface

Displays:

* READY
* TV STARTS
* TV RUNNING
* TV OFF
* CARD USED
* RESET
* INVALID


## Hardware Components

* Arduino Nano
* MFRC522 RFID Reader
* RFID Cards ×2
* RFID Reset Tag ×1
* SSD1306 OLED Display (128×64)
* Relay Module
* LED
* Breadboard
* Jumper Wires
* Power Supply


## Software and Libraries

### Software

* Arduino IDE

### Libraries

* SPI
* MFRC522
* Wire
* Adafruit GFX
* Adafruit SSD1306


## Working Principle

1. System waits for an RFID card.
2. RFID UID is read and validated.
3. If Card 1 is scanned:

   * Appliance turns ON for 20 seconds.
   * Card becomes unavailable.
4. If Card 2 is scanned:

   * Appliance turns ON for 40 seconds.
   * Card becomes unavailable.
5. If Reset Card is scanned:

   * Card permissions are restored.
6. Invalid cards are rejected.


## Technical Concepts Demonstrated

* RFID Authentication
* Access Control Systems
* Embedded Systems Programming
* State Management
* Relay-Based Automation
* OLED Display Communication
* SPI Communication
* Event-Driven Logic


## Project Structure
``````
rfid-access-control-system/
├── Arduino_Code/
│ └── rfid_access_control.ino
├── Images/
├── Videos/
├── Circuit_Diagram/
└── README.md
``````

## My Contribution

This RFID system was fully implemented by me, including:

* Hardware integration
* RFID reader configuration
* UID authentication logic
* OLED display interface
* Relay control
* LED control
* Timer implementation
* Testing and debugging

The system was later integrated into a Smart Home project demonstration.


## Applications

* Smart Home Access Systems
* Appliance Control Systems
* Membership Verification
* Attendance Systems
* Secure Device Access
* Educational IoT Demonstrations


## Future Improvements

* Wi-Fi Connectivity
* Mobile Application Integration
* Database Logging
* Multiple User Profiles
* Cloud Dashboard
* Access History Tracking
