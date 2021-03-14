# Project3-IoT
A 2nd semester project - monitoring ideal study conditions at BAAA.

In this project I co-developed a prototype monitoring ideal study conditions (temperature, humidity and light) at the Business Academy Aarhus. 

The project was developed using ESP8266 Wi-Fi microchip, Arduino board, GPS module and Python Flask.

The prototype is placed in specific location and runs on low-power mode, only checking for light conditions. Once the lights turn on in the room the prototype is in,
the prototype "wakes up" and starts monitoring the conditions. At the same time, it constantly sends data to a webserver, where the user can see the current conditions
measured by the prototype, its location on the map, as well as the location of all other active prototypes, see how the conditions change overtime etc.
