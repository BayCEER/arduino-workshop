#!/usr/bin/python3
from time import sleep
from bayeosgatewayclient import BayEOSWriter, BayEOSSender
import tempfile
from os import path
import math 
import board
from adafruit_bme280 import basic as adafruit_bme280

# Create sensor object, using the board's default I2C bus.
i2c = board.I2C()  # uses board.SCL and board.SDA
# i2c = board.STEMMA_I2C()  # For using the built-in STEMMA QT connector on a microcontroller
bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c, address=0x76)

NAME = 'Pi-zero-BME280'
URL = 'http://bayeos.bayceer.uni-bayreuth.de/gateway/frame/saveFlat'
USER= 'import@Workshop'
# TODO:Please change
PASSWORD = 'import'
PATH = path.join(tempfile.gettempdir(),NAME)

# Create a writer thread 
writer = BayEOSWriter(PATH,max_time=5)
writer.save_msg('Writer was started.')

# Create a sender thread
sender = BayEOSSender(PATH, NAME, URL,user=USER,password=PASSWORD)
sender.start()

while True:   
    writer.save({'temp':bme280.temperature,
    'humidity':bme280.relative_humidity,
    'pressure':bme280.pressure})    
    sleep(2)
