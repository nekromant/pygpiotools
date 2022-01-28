def create(driver, device):
    print(f"opening {driver} dev {device}")
    return 123

def direction(handle, pin, direction):
    print(f"direction handle: {handle}, pin {pin} {direction}")

def write(handle, pin, value):
    print(f"write handle: {handle}, pin {pin} {value}")

def read(handle, pin):
    print(f"read handle: {handle}, pin {pin}")
    return 1;
