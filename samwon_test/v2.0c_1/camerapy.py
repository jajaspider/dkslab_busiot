import RPi.GPIO as GPIO
from picamera import PiCamera
from time import sleep

Button = 15

GPIO.setmode(GPIO.BCM)
GPIO.setup(Button, GPIO.IN)


camera = PiCamera()

def CameraPreview():
        camera.start_preview()
        while True:
                if GPIO.input(Button) == True:
                        camera.capture('/home/pi/Desktop/snapshot.jpg')
                        camera.stop_preview()
                        camera.close()
                        GPIO.cleanup()
                        break
CameraPreview()
