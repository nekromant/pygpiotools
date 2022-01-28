import pygpiotools
import usb.core
import usb.util


VID = 0x10c4
PID = 0xea60

def create(driver, device):
    handle = pygpiotools.tty_to_usbdev(device, VID, PID)
    return handle

def __read_latch_register(device, reg_num):
    buffer = device.ctrl_transfer(
        usb.util.build_request_type(usb.util.CTRL_IN, usb.util.CTRL_TYPE_VENDOR, usb.util.CTRL_RECIPIENT_DEVICE),
        0xff,
        0xc2,
        0,
        1,
        1000)
    return buffer[0]

def __write_latch_register(device, reg_num, value):
    device.ctrl_transfer(
        usb.util.build_request_type(usb.util.CTRL_OUT, usb.util.CTRL_TYPE_VENDOR, usb.util.CTRL_RECIPIENT_DEVICE),
        0xff,
        0x37e1,
        value,
        None,
        1000)

def set_gpio_out(device, gpio, v):
    dir_reg_value = __read_pl2303_reg(device, gpio.dir_reg)
    dir_reg_value |= gpio.dir_mask
    __write_pl2303_reg(gpio.dir_reg, dir_reg_value)

    out_reg_value = __read_pl2303_reg(device, gpio.out_reg)
    if v:
        out_reg_value |= gpio.out_mask
    else:
        out_reg_value &= ~gpio.out_mask
    __write_pl2303_reg(device, gpio.out_reg, out_reg_value)


def direction(handle, pin, direction):
    gpio = pin_to_gpio(pin)  
    dir_reg_value = __read_pl2303_reg(handle, gpio.dir_reg)
    dir_reg_value |= gpio.dir_mask
    __write_pl2303_reg(handle, gpio.dir_reg, dir_reg_value)

def write(handle, pin, value):
    gpio = pin_to_gpio(pin)
    out_reg_value = __read_pl2303_reg(handle, gpio.out_reg)
    if value:
        out_reg_value |= gpio.out_mask
    else:
        out_reg_value &= ~gpio.out_mask
    __write_pl2303_reg(handle, gpio.out_reg, out_reg_value)


def read(handle, pin):
    raise Exception("NOT YET IMPLEMENTED")
    #print(f"read handle: {handle}, pin {pin}")
    return 1;
