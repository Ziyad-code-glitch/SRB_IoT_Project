# SRB - Smart Rubbish Bin Project

Welcome to the **SRB** (Smart Rubbish Bin) project! This IoT-based system automates the monitoring and management of rubbish levels in bins using sensors and servo motors, providing real-time updates through the Blynk platform. Designed to streamline waste collection, this project aims to reduce human intervention and make waste management more efficient.

## 📖 About This Project

The SRB project leverages IoT technologies to create a smart, automated waste management system. It uses ultrasonic sensors to detect rubbish levels, LEDs to indicate bin status, and servo motors to automatically open and close the trash bin lid. The system connects to the Blynk app for real-time monitoring, notifications, and remote control.

## 🚀 Key Features

- **Ultrasonic Sensors**: Two ultrasonic sensors measure the bin’s rubbish levels and the proximity of objects near the bin lid.
- **Automatic Lid Control**: The servo motor opens and closes the bin lid based on the proximity of the user.
- **LED Status Indicators**: Red, yellow, and green LEDs indicate the fill level of the bin (empty, normal, full).
- **Blynk Integration**: Real-time monitoring of bin status, percentage of bin fill, and control of the bin lid via the Blynk app.
- **Event Logging**: Logs the "full bin" event and notifies the Blynk app.
- **Wi-Fi Connectivity**: Connects to the Blynk platform over Wi-Fi using ESP8266.

## 🛠️ Technologies Used

- **Blynk**: For real-time IoT monitoring and control.
- **ESP8266**: Wi-Fi module for communication.
- **Ultrasonic Sensors**: Measures the fill level of the bin.
- **Servo Motor**: Controls the opening and closing of the bin lid.
- **LEDs**: Status indicators for bin levels (empty, normal, full).
- **Arduino Uno**: Microcontroller to manage sensors and control logic.
- **Software Serial Library**: Used for communication between Arduino and ESP8266.

## 📂 Project Structure

### Components:
- **Ultrasonic Sensor 1**: Detects the rubbish level in the bin and updates the percentage.
- **Ultrasonic Sensor 2**: Detects the proximity of a user and triggers the automatic lid opening/closing.
- **Servo Motor**: Controls the bin lid based on sensor readings.
- **LEDs**: Provide a visual indication of the bin's fill status.

### Functions:
1. **Distance Measurement (ultrasonicSensor_1 & ultrasonicSensor_2)**:
   - Uses the ultrasonic sensors to measure the distance to the rubbish or nearby objects.
   - Updates the bin fill percentage for the first sensor and proximity for the second sensor.
   
2. **Check Bin Status (checkPercentage)**:
   - Adjusts the LED indicators based on the rubbish level percentage.
   - Sends a "full bin" notification to Blynk when the bin is more than 75% full.

3. **Open/Close Trash Bin (openTrash & closeTrash)**:
   - Opens or closes the bin lid automatically when the user is within range.
   
4. **Blynk App Control**:
   - Updates bin status and servo position in the Blynk app.
   - Allows manual control of the bin lid via the Blynk app.

## 🛠️ How It Works

1. **Ultrasonic Sensor 1**: Measures the distance from the rubbish inside the bin. The system maps this distance to a percentage (0-100%) to show how full the bin is.
2. **Ultrasonic Sensor 2**: Detects the presence of a user near the bin, opening the lid automatically when a user is detected.
3. **Servo Motor**: Controls the opening and closing of the bin lid. The lid opens when a user is nearby and closes after 5 seconds or when no user is detected.
4. **LED Indicators**: 
   - **Red LED**: Bin is full (75-100%).
   - **Yellow LED**: Bin is partially full (20-75%).
   - **Green LED**: Bin is empty (0-20%).
5. **Blynk App**: Provides real-time updates on bin status, fill percentage, and manual control of the bin lid.

## 🔧 Code Walkthrough

### Libraries Used
- **Servo.h**: Controls the servo motor.
- **ESP8266_Lib.h**: Manages communication with the ESP8266 module.
- **BlynkSimpleShieldEsp8266.h**: Connects the device to the Blynk app.

### Key Functions
- **ultrasonicSensor_1 & ultrasonicSensor_2**: Measure the distance and calculate rubbish level or proximity to the user.
- **checkPercentage**: Controls the LEDs based on bin fill percentage and sends notifications when the bin is full.
- **openTrash & closeTrash**: Open and close the bin lid based on sensor readings or commands from the Blynk app.
- **myTimer**: Sends periodic updates to the Blynk app every second.

## 💬 Feedback and Contact

I would love to hear your feedback! Feel free to reach out to me via:

- **Email**: [wziyad891@gmail.com](mailto:wziyad891@gmail.com)
- **LinkedIn**: [Ziyad Walid](https://www.linkedin.com/in/ziyad-walid/)
- **GitHub**: [ziyad-code-glitch](https://github.com/ziyad-code-glitch)
