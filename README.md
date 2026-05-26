# ESP32-WiFi-Provisioning
ESP32 Wi-Fi Provisioning system using Access Point mode and local Web Server for wireless Wi-Fi configuration without re-uploading firmware.

---

## ESP32 Wi-Fi Provisioning System 🔧📶

Have you ever wondered how smart home devices like smart lamps, CCTV, or IoT devices connect to Wi-Fi without needing to reprogram them every time the network changes?

This project demonstrates a simple but powerful **Wi-Fi provisioning system using ESP32**, allowing users to configure Wi-Fi credentials through a web interface without modifying or re-uploading firmware.

---

## 🚀 Features

- Wi-Fi configuration via **local web page**
- Access Point (AP) mode for initial setup
- Automatic reconnection using saved credentials
- Persistent storage using **Preferences (NVS)**
- LED status indicator:
  - Slow blink → connecting to Wi-Fi
  - Fast blink → hotspot (AP mode)
- 20-second connection timeout system
- Works with 2.4 GHz Wi-Fi networks

---

## ⚙️ How It Works

1. ESP32 starts and reads saved Wi-Fi credentials from NVS memory  
2. It tries to connect to the saved Wi-Fi network  
3. If successful → device runs normally  
4. If it fails within 20 seconds → ESP32 switches to Access Point mode  
5. ESP32 creates a hotspot and hosts a web server at: 192.168.4.1
6. User connects to the hotspot and enters new Wi-Fi credentials  
7. Data is saved and ESP32 restarts automatically  
8. Device reconnects using the new configuration  

---

## 🧠 Concepts Used

- Wi-Fi Provisioning
- Access Point (AP) Mode
- Web Server (ESP32)
- Non-Volatile Storage (Preferences / NVS)
- Embedded System State Control
- Basic IoT Networking

> Note: This project uses Wi-Fi Provisioning, NOT OTA (Over-The-Air update). OTA is used for firmware updates, while this project is focused on network configuration.

---

## 🛠 Hardware Used

- ESP32 Dev Board
- Built-in LED indicator
- Wi-Fi router (2.4 GHz)

---

## 📁 Project Structure

ESP32-WiFi-Provisioning/
│
├── ESP32-WiFi-Provisioning.ino
│
├── docs/
│   └── images
│
├── .gitignore
├── LICENSE
└── README.md

---

## 🔮 Future Improvements

- Captive portal auto redirect
- Mobile-friendly UI improvement
- OTA firmware update integration
- Reset button (factory reset)
- MQTT / IoT cloud integration

---

## 📌 Author

Built as part of embedded systems and IoT learning journey using ESP32.

Feel free to connect and collaborate on IoT & embedded projects 🚀
