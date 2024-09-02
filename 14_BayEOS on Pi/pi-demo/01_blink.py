import RPi.GPIO as GPIO
from time import sleep

PIN = 29

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(PIN, GPIO.OUT, initial=GPIO.LOW)

while True: # Run forever
    GPIO.output(PIN, GPIO.HIGH) # Turn on
    sleep(1)                    # Sleep for 1 second
    GPIO.output(PIN, GPIO.LOW)  # Turn off
    sleep(1)                    # Sleep for 1 second


