# Tunnel-Rover

ESP32-CAM module for live video streaming and an ESP8266 for sensor data collection, both accessible via a web interface. The system operates in access point mode with a static IP address, ensuring secure access limited to authorized personnel. With this setup, one designated user can remotely control the rover's operations and monitor tunnel conditions for safety and efficiency.

Most importantly i use 2 microcontrollers to get video feed and control the rover,that because some how controling microcontroller(esp8266) damage i can still get the video feed.

Features:

    Web Interface Control: Control the ESP32-CAM and ESP8266 rover functionalities through a user-friendly web interface.
    Live Video Streaming: Stream live video feed from the ESP32-CAM module to monitor tunnel conditions in real time.
    Sensor Data Collection: Gather data on toxic gas levels, temperature, and humidity using the ESP8266 and display to the user through the web server.
    Access Point Mode: Operate the system in access point mode with a static IP address for secure and restricted access it is easy to user to log in.
    Remote Operation: Control rover functions and monitor tunnel conditions remotely, minimizing human risk.

Technologies Used:

    ESP32-CAM and ESP8266: Enable web-controlled rover functionalities and data collection.
    Web Interface: Access and control rover operations through a user-friendly web interface.
    Access Point Mode: Establish a secure access point with a static IP address for restricted access.
    Live Video Streaming: Stream video feed from the ESP32-CAM module for real-time monitoring.
    Sensor Data Collection: Gather data on toxic gas levels, temperature, and humidity using the dht-11/22 and any gas sensors like MQ2 / MQ5 / MQ6 / MQ4.

How It Works:

    Access Point Setup: The ESP32-CAM and ESP8266 modules create an access point with a static IP address, ensuring secure and controlled access.
    Web Interface: The designated user accesses the web interface to control rover operations and view live video streaming and sensor data.
    Remote Control: Through the web interface, the user can navigate the rover, adjust suspension settings, and monitor tunnel conditions.
    Real-Time Monitoring: Live video streaming and sensor data provide real-time insights into tunnel conditions, enabling informed decision-making.

