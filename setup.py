import os
import pygpiotools
from setuptools import setup
from distutils.core import Extension

fh = open("README.md", "r")
long_description = fh.read()

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
       include_package_data=True,
       install_requires = install_requires,
       description = 'Python tools & API to control GPIO pins of common USB_to_UART converters',
       ext_modules = modules,
       long_description_content_type='text/markdown',
       long_description = long_description
       )