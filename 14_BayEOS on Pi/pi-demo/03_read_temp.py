#!/usr/bin/env python3
from w1thermsensor import W1ThermSensor, Sensor

sensor = W1ThermSensor(Sensor.DS18B20,"0214646739ff")
print("Sensor %s has temperature %.2f" % (sensor.id, sensor.get_temperature()))
