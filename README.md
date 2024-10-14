# greenhouse-temperature-and-humidty-control arduino uno
using gsm,blynk(account),dht11,

Greenhouse Controller for Temperature and Humidity  using arduino

1. Introduction

The Greenhouse Controller is designed to automate and monitor environmental conditions in a greenhouse, specifically focusing on temperature and humidity. It uses an array of sensors and actuators to control the environment, ensuring optimal conditions for plant growth. The system integrates with the Blynk IoT platform for remote monitoring and control, providing users with real-time data and alerts via mobile devices.

This project employs components like the DHT11 sensor, a buzzer, fan, GSM module, 16x2 LCD, water valve, and an Arduino Uno to manage temperature and humidity levels. The system automatically triggers alerts, controls cooling, and can be accessed remotely through the Blynk app.

2. Objectives
- To monitor temperature and humidity levels in a greenhouse.
- To automate cooling mechanisms when temperature exceeds predefined thresholds.
- To provide real-time data and notifications using the Blynk app and GSM module.
- To display real-time data on an LCD screen within the greenhouse.
- To control the water valve based on the environmental conditions.

3. Components Used
1. DHT11 Sensor: Measures temperature and humidity inside the greenhouse.
2. Buzzer: Alerts when temperature or humidity exceeds set limits.
3. Fan: Activated when the temperature is too high to cool down the environment.
4. GSM Module: Sends SMS alerts for critical conditions (e.g., high temperature or humidity).
5. 16x2 LCD: Displays temperature and humidity data in real-time.
6. Water Valve: Controls water flow based on environmental conditions.
7. Arduino Uno: The microcontroller that manages the entire system.
8. Blynk App: Provides real-time data monitoring and control via smartphone.
   
4. System Design
The greenhouse controller works through a feedback system. The DHT11 sensor continuously monitors temperature and humidity levels inside the greenhouse. The data is processed by the Arduino Uno, which takes appropriate action based on predefined thresholds.

- Cooling Mechanism: If the temperature exceeds the set limit, the fan is turned on to cool the greenhouse.
- Humidity Control: The system can activate the water valve to regulate humidity levels.
- Alerts: If critical temperature or humidity levels are reached, the buzzer sounds, and an SMS alert is sent using the GSM module.
- Display and Monitoring: The LCD displays real-time temperature and humidity readings, while the Blynk app allows remote access to the data.

5. Features
- Automated Cooling: Fan control is based on temperature thresholds.
- SMS Alerts: Users receive text messages in case of extreme conditions.
- Real-time Monitoring: Data is displayed on the 16x2 LCD and accessible remotely via the Blynk app.
- Remote Control: Through Blynk, users can manually activate/deactivate the fan or water valve.

6. Software Implementation
The software for the greenhouse controller is written in Arduino IDE. It involves:
- Reading sensor data from the DHT11.
- Displaying data on the LCD.
- Sending data to Blynk for remote monitoring.
- Triggering the fan, buzzer, and water valve based on predefined thresholds.
- Sending SMS alerts via the GSM module.

7. Conclusion
This greenhouse controller provides an efficient solution for automating temperature and humidity management, integrating both local and remote monitoring options through the use of Blynk. It ensures optimal environmental conditions for plant growth, improving overall productivity.


