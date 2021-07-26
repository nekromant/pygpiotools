import sys
import os
from parse import parse
import usb.core
import usb.util


__driver_list = ["dummy", "pl2303"]
__drivers = {}
__lookup = {}

def list():
    return __driver_list

#Returns a handle for the device
def open(driver, port):
    #Lazy import here

    if not driver in __drivers and driver in __driver_list:
        drv = getattr(__import__("pygpiotools", fromlist=[driver]), driver)
        __drivers[driver] = drv
    else:
        drv = __drivers[driver]
    handle = drv.open(driver, port)
    if handle != None: 
        __lookup[handle] = drv
    return handle

def __handle_to_drv(handle):
    if not handle in __lookup:
        raise Exception("Invalid handle")
    drv = __lookup[handle]
    return drv

def direction(handle, pin, direction):
    drv = __handle_to_drv(handle)
    return drv.direction(handle, pin, direction)

def write(handle, pin, value):
    drv = __handle_to_drv(handle)
    return drv.write(handle, pin, value)

def read(handle, pin):
    drv = __handle_to_drv(handle)
    return drv.read(handle, pin)


class _usb_find_class(object):
    def __init__(self, usb_path):
        self.usb_path = usb_path

    def device_usb_path(self, dev):
        result = str(dev.bus) + "-" + str(dev.port_numbers[0])
        for i in range(1, len(dev.port_numbers)):
            result += "." + str(dev.port_numbers[i])
        return result

    def __call__(self, dev):
        return self.device_usb_path(dev) == self.usb_path

def tty_to_usbdev(tty, vid, pid):
    tty = os.path.realpath(tty)
    parsed_tty = parse("/dev/tty{}{:d}", tty, case_sensitive=True)
    if not parsed_tty:
        raise Exception("cannot parse port string: " + tty)
    tty = "tty" + parsed_tty[0] + str(parsed_tty[1])

    # get USB path for tty (like "1-1.1.3")
    sys_path = os.path.realpath("/sys/bus/usb-serial/devices/" + tty)
    usb_path = sys_path.split("/")[-2].split(":")[0]

    # find the device
    usb_dev = usb.core.find(custom_match=_usb_find_class(usb_path), idVendor=0x67b, idProduct=0x2303)
    if not usb_dev:
        raise Exception("cannot find pl2303 device by usb path: " + usb_path)
    return usb_dev