#!/usr/bin/python3
import time
import psutil

from bayeosdevice.device import DeviceController
from bayeosdevice.item import ItemDict

# Model
values = ItemDict({"cpu1":None})
units = {"^cpu":'%',"\w+time$":'secs'}
actions = ItemDict({"sleep_time":10, "run": True})

# Controller
con = DeviceController(values,actions,units)
con.start()

try:
    while True:
        if (actions["run"] == True):
            cpu = psutil.cpu_percent(percpu=True)
            values['cpu1'] = cpu[0]
            time.sleep(actions["sleep_time"])
        else:
            time.sleep(0.01)
except KeyboardInterrupt:
    print('Exit')
