import pygpiotools
import time

print(f"Drivers loaded: {pygpiotools.list()}")
#handle = pygpiotools.open("pl2303", "/dev/ttyUSB0")
handle = pygpiotools.open("pl2303", "com4")
print(pygpiotools.__registry)
print("handle: ", handle)
#handle = pygpiotools.open("dummy", "/dev/ttyUSB0")
#print(handle)

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

