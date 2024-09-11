#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, signal
from w1thermsensor import W1ThermSensor, Sensor
from bayeosgatewayclient import BayEOSWriter, BayEOSSender
from time import sleep
from bayeosdevice.device import DeviceController
from bayeosdevice.item import ItemDict
import logging
import json
import RPi.GPIO as GPIO

# Init LED 
LED_RED = 29
LED_GREEN = 35

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

GPIO.setup(LED_RED, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(LED_GREEN, GPIO.OUT, initial=GPIO.LOW)

with open("./config.json") as f:
        conf = json.load(f)

logging.basicConfig(format='%(asctime)s %(levelname)s:%(message)s',level=conf["log_level"]) 

def sigterm_handler(_signo, _stack_frame):
    sys.exit(0)    

signal.signal(signal.SIGTERM, sigterm_handler) 
signal.signal(signal.SIGINT, sigterm_handler)

writer = BayEOSWriter(path=conf['path'],max_time=conf['max_time'])
writer.save_msg('Writer was started.')

sender = BayEOSSender(path=conf['path'], name=conf['name'],url=conf['gateway']['url'],
user=conf['gateway']['user'],password=conf['gateway']['password'])
sender.start() # sender runs in a concurrent thread

sensor = W1ThermSensor(Sensor.DS18B20,"0214646739ff")


values = ItemDict({"Temperature":None})
units = {"Temperature":'°C',"\w+time$":'secs'}
settings = ItemDict({"sleep_time":conf["sleep_time"], "run": True, "led_red": False, "led_green":False})

controller = DeviceController(values,settings,units)
controller.start()

while True:  
    if (settings["run"] == True):
        # Read sensor
        values["Temperature"] = sensor.get_temperature()
        writer.save(values,0x61)

        # Toggle actuators
        GPIO.output(LED_RED,settings['led_red'])
        GPIO.output(LED_GREEN,settings['led_green'])


        sleep(settings["sleep_time"])            
    else:
        sleep(0.01)




