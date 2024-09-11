#!/usr/bin/python
# -*- coding: utf-8 -*-
from w1thermsensor import W1ThermSensor, Sensor
from bayeosgatewayclient import BayEOSWriter, BayEOSSender
from time import sleep
import logging
import json

with open("./config.json") as f:
        conf = json.load(f)

logging.basicConfig(format='%(asctime)s %(levelname)s:%(message)s',level=conf["log_level"]) 

writer = BayEOSWriter(path=conf['path'],max_time=conf['max_time'])
writer.save_msg('Writer was started.')

sender = BayEOSSender(path=conf['path'], name=conf['name'],url=conf['gateway']['url'],
user=conf['gateway']['user'],password=conf['gateway']['password'])
sender.start() # sender runs in a concurrent thread

sensor = W1ThermSensor(Sensor.DS18B20,"0214646739ff")
    
while True:
    logging.info('Adding frame')
    writer.save([sensor.get_temperature()])
    sleep(conf["sleep_time"])


 
