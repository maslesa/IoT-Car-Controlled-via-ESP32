ESP32-Based Car Control via Web Server  

This project demonstrates how to control a car using an ESP32 microcontroller through a simple web interface. The car's movements, including forward, backward, left, and right turns, are managed via motor drivers connected to the ESP32. Users can access the web interface from any device to control the car in real time using keyboard inputs.

## Features  
- Real-time control of a car using a web browser.  
- Keyboard inputs (`W`, `A`, `S`, `D`) to move forward, left, backward, and right.  
- Simple, lightweight web interface.  
- Motor control using an L298N motor driver for DC motors.  
- Wi-Fi connectivity for remote access.  

## Components Required  
- ESP32 microcontroller  
- L298N motor driver  
- DC motors (2 or 4 depending on design)  
- Power supply (appropriate for the motor requirements)  

## Pin Configuration  
| ESP32 Pin | Component  |
|-----------|------------|
| 18        | IN1 (Motor 1) |
| 19        | IN2 (Motor 1) |
| 21        | IN3 (Motor 2) |
| 22        | IN4 (Motor 2) |
| 23        | Wi-Fi Status LED |

