import os
import pygpiotools
from distutils.core import setup, Extension

if os.name == 'nt':
       #Windows is the usual mess. We'll need a native extension
       pygptools = Extension('pygpiotools',
                           sources = ['gpio-windows.c', "pl2303.c"])
       modules = [pygptools]
       define_macros = [('PYGPIOTOOLS_VERSION', pygpiotools.__version__)],
       install_requires = []
       packages = []
else:
       #libusb for all the unix folks, no native stuff
       modules = []
       install_requires = [
              "pyusb>=1.0.0",
              ]
       packages = ["pygpiotools"]

setup( 
       name = 'pygpiotools',
       version = pygpiotools.__version__,
       packages=packages,
       install_requires = install_requires,
       description = 'Python tools & API to control GPIO pins of common USB_to_UART converters',
       ext_modules = modules,
       )