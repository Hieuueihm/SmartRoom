# Smart Room - Smart home solutions for everyone's life 

## Introduction
- This project is in the numerical measurement and controls course ( ELT-3207 ), University of Engineering and Technology.
- The software for user is developed with React Native programming language for the Front-end, NodeJS for the Back-end, using the sensors and peripheral hardware attached to the Stm32f103c8t6 and use the ESP32 board's wifi
- The project also includes a website for managers, which is convenient for managing and accessing information in the building.

## Authors

- [Nguyen Minh Hieu - 21020908, UET-VNU](https://github.com/Hieuueihm)

- [Vu Tuan Anh - 21020429, UET-VNU](https://github.com/VuTuanAnh-1368)

- [Nguyen Viet Duc - 21020904, UET-VNU](https://github.com/vieedu3vif)


## Folder Structure
SmartRoom/
├── ADHApp: mobile application.
├── ESP32_WS: esp32 web server.
├── Hardwares: includes C code built from scratch for our sensors, actuators, ... 
├── Server: provides api for our applications.
├── Web: admin webpage.
└── README.md
## Hardware description and programing languages

### Hardwares

-  DC Servo SG90
-  Humidity and temperature sensor DHT11
-  Gas sensor MQ135
-  IR sensors
-  Flame sensor
-  5V Relay 
-  STM32F103c8t6( blue pill ) MCU
-  ESP32 CH340 wifi board
-  DC fans
-  5V LCD 1602

### Protocol
Using the MQTT protocol to send and receive messages.

### Software programing languages
- Front-end: React-Native
- Back-end: NodeJS
- Database: MongoDB

## Features
### For user
- Login, logout
- Tracking the weather and UV rays 
- Tracking the humidity and temperatures in the room
- Auto open/close the door and turn on/off the light when the person comes in or out
- Controll the brightness of the light
- Detect and warn when there is a fire or gas detection and automatically implement emergency escape solutions.


###  For manager
- Add or remove 1 or more users in management area

## Demo
[Video demo on Youtube](https://www.youtube.com/watch?v=RIVCSrlv5GM)

