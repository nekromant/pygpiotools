import pygpiotools
import time
import serial

print(pygpiotools.__version__)
#print(f"Drivers loaded: {pygpiotools.list()}")
#handle = pygpiotools.open("pl2303", "/dev/ttyUSB0")
#handle = pygpiotools.open("pl2303", "com5")
#ser = serial.Serial('com5:', 1000000)
ser = serial.Serial('/dev/ttyUSB0', 1000000)
print(ser, ser._port)

handle = pygpiotools.connect_pyserial("pl2303", ser)
#print(pygpiotools.__registry)
#print("handle: ", handle)
#handle = pygpiotools.open("dummy", "/dev/ttyUSB0")
#print(handle)

while True:
    pygpiotools.direction(handle, 0, "OUTPUT")
    pygpiotools.direction(handle, 1, "OUTPUT")
    
    pygpiotools.write(handle, 0, 0)
    pygpiotools.write(handle, 1, 0)
    time.sleep(1)
    pygpiotools.write(handle, 0, 1)
    pygpiotools.write(handle, 1, 1)
    time.sleep(1)
    pygpiotools.write(handle, 0, 0)
    pygpiotools.write(handle, 1, 0)
    #pygpiotools.read(handle, 1)

