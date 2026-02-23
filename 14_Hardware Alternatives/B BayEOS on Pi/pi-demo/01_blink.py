import lgpio
import sys
from time import sleep

LED = 5 # RED: GPIO5, GREEN: GPIO19

handle = lgpio.gpiochip_open(0)
if handle < 0:
   print("GPIO Error")
   sys.exit(-1)
   

lgpio.gpio_claim_output(handle, LED,0)

# Flashes led four times 
for i in range(0,4):    
    lgpio.gpio_write(handle, LED, 1)    
    sleep(1) # Sleep for 1 second
    lgpio.gpio_write(handle, LED, 0)    
    sleep(1) # Sleep for 1 second

lgpio.gpio_free(handle, LED)
sys.exit(0)
    



