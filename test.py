import pygpiotools

print(f"Drivers loaded: {pygpiotools.list()}")
handle = pygpiotools.open("pl2303", "/dev/ttyUSB0")

#handle = pygpiotools.open("dummy", "/dev/ttyUSB0")
#print(handle)

pygpiotools.direction(handle, 0, "OUT")
pygpiotools.direction(handle, 1, "OUT")
pygpiotools.write(handle, 0, 0)
pygpiotools.write(handle, 1, 0)

#pygpiotools.read(handle, 1)

