📊 Data Logger with SD Card and RTC

📌 Project Overview:

This project implements a Data Logger System that records sensor data along with accurate date and time using a Real Time Clock (RTC) module and stores the data into an SD card.
The system ensures reliable data storage for monitoring and analysis applications.

🎯 Objectives:

To interface SD Card with microcontroller
To interface RTC module for real-time timestamp
To log sensor data with date and time
To store data in .txt or .csv format
To retrieve stored data for analysis

🛠️ Components Used:

Microcontroller ESP 32
SD Card Module
RTC Module DS1307
Temperature Sensor DHT11
Power Supply
Connecting Wires

⚙️ Working Principle:

RTC provides current date and time.
Sensor reads environmental data.
Microcontroller collects sensor data.
Data is combined with timestamp.
Data is stored in SD card file.
Stored file can be opened in PC for analysis.

🔌 Hardware Connections:

SD Card Module:
MISO → Microcontroller MISO
MOSI → Microcontroller MOSI
SCK → Microcontroller SCK
CS → Chip Select Pin
VCC → 3.3V / 5V
GND → GND

RTC Module:

SDA → I2C SDA
SCL → I2C SCL
VCC → 5V
GND → GND

💻 Software Requirements:

Embedded C / Arduino IDE
Keil uVision (if LPC1768)
FatFs Library (for SD card)
Serial Monitor (for debugging)

📂 Output Format:

Date       Time       Temperature
27-02-2026 10:35:20   28.5°C
27-02-2026 10:36:20   28.7°C

📈 Applications:

Weather Monitoring
Industrial Data Logging
Environmental Monitoring
IoT Based Projects
Laboratory Experiments

🚀 Future Improvements:

Add WiFi for cloud upload
Add LCD display
Add multiple sensors
Add data encryption
Web-based monitoring dashboard

