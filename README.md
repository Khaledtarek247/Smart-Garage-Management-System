## Description:
The Smart Garage Management System is an advanced embedded systems project designed to streamline and automate the process of managing a parking garage. 
This project utilizes a combination of sensors, an ATmega 32 microcontroller, and communication technologies to create an efficient and user-friendly system for monitoring and controlling garage operations.
## Features:
1- Entrance and Exit Gate Monitoring:
  
  IR Sensors: Integrated at both the entrance and exit gates to detect the presence of vehicles. These sensors provide real-time data to the microcontroller, enabling automatic gate control.
  
2-Parking Slot Monitoring:
  
  Ultrasonic Sensor: Deployed to measure the distance to objects in the parking slots, ensuring accurate detection of available and occupied spaces.
  
  IR Sensors: Additional sensors positioned within the parking area to verify the status of each slot.
  
3-Gate Control:
  
  Servo Motor: Acts as the gate mechanism, opening and closing based on sensor input or user commands.
  
4-Temperature Monitoring:
  
  LM35 Temperature Sensor: Continuously monitors the garage temperature to detect potential fire hazards, triggering alarms if necessary.
  
5-Dual Control Modes:
  
  Automatic Mode: The system autonomously controls the entrance and exit gates based on sensor readings, providing a seamless and hands-free experience for users.
  
  Voice Recognition Mode: Users can control the gates via voice commands through a Python application. This application communicates with the microcontroller using UART, enhancing the system's accessibility and convenience.
"# Smart-Garage-Management-System" 
