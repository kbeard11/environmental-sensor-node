# environmental-sensor-node
ESP32-based environmental monitoring node for collecting temperature, humidity, light and soil moisture data with automated cloud logging.

Environmental Monitoring Node
ESP32-C3 based environmental monitoring platform developed for plant health monitoring, environmental data collection and field-trial applications. The system integrates temperature, humidity, light intensity and soil moisture sensors with automated cloud-based logging, weather forecasting and reporting workflows.

Features
- Temperature and relative humidity monitoring (Adafruit SHT40)
- Ambient light monitoring (BH1750)
- Soil moisture monitoring via ADS1015 ADC and capacitive moisture probes
- Automated Wi-Fi data transmission to Google Sheets
- Weather forecast integration using the Open-Meteo API
- Automated weekly email reporting via Google Apps Script
- Built-in Wi-Fi reconnection and recovery mechanisms
- Designed for long-term indoor and outdoor environmental monitoring

Hardware
- SparkFun Pro Micro ESP32-C3
- Adafruit SHT40 Temperature & Humidity Sensor
- BH1750 Ambient Light Sensor
- ADS1015 Analogue-to-Digital Converter
- Capacitive Soil Moisture Sensors
  
Software Stack
- Arduino / C++
- Google Apps Script
- Google Sheets
- Python
- Open-Meteo API
  
Applications
- Plant health monitoring
- Environmental monitoring
- Field-trial instrumentation
- Pollinator habitat monitoring
- Automated environmental data collection
- IoT and sensor network prototyping
  
Future Enhancements
- ESP32-S3 camera integration for native bee monitoring
- Solar and battery-powered deployment
- Local SD card data backup
- LoRa communication for remote monitoring
- Automated alerts and anomaly detection
- Image-based pollinator activity analysis
