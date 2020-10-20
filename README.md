# Thermometer-MQTT Alura

This a project made on a course from Alura, for a MQTT Thermometer.

There is a Script which runs on a Linux Machine (On the course a Raspberry Pi is used).

## Installation 

On the Linux machine (MQTT Broker) you must have:
* ### Mosquitto MQTT

To install Mosquitto (the MQTT Broker) on a debian based distro (Raspian, Debian, Ubuntu...)
```shell
$ sudo apt-get install mosquitto
```
You may also compile from source or look for it on you distro using yum, zipper or whichever packet manager you use

* ### Python 3 - Paho MQTT
To run the # Python 3 # scripts, install [Paho-MQTT](https://pypi.org/project/paho-mqtt/):
```python
pip install paho-mqtt
```

