#!/usr/bin/python3
from time import sleep
from bayeosgatewayclient import BayEOSWriter, BayEOSSender
import tempfile
from os import path
import math 

NAME = 'Pi-zero'
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

# Produce some values 
nr=0
angle = 0
while True:
    writer.save([nr,angle ,10*math.sin(angle)])    
    nr+=1
    angle+=0.1
    if angle > 360:
        angle = 0
    sleep(0.5)
