import os
from setuptools import setup
from distutils.core import Extension

fh = open("README.md", "r")
long_description = fh.read()

exec(open('pygpiotools/_version.py').read())

if os.name == 'nt':
       #Windows is the usual mess. We'll need a native extension
       pygptools = Extension('pygpiotools',
                           sources = ['gpio-windows.c', "pl2303.c"])
       modules = [pygptools]
       define_macros = [('PYGPIOTOOLS_VERSION', __version__)],
       install_requires = []
       packages = []
else:
       #libusb for all the unix folks, no native stuff
       modules = []
       install_requires = [
              "pyusb>=1.0.0",
              "parse"
              ]
       packages = ["pygpiotools"]

setup( 
       name = 'pygpiotools',
       version = __version__,
       packages=packages,
       include_package_data=True,
       install_requires = install_requires,
       description = 'Python tools & API to control GPIO pins of common USB_to_UART converters',
       ext_modules = modules,
       long_description_content_type='text/markdown',
       long_description = long_description,
       url = "http://github.com/RC-MODULE/rumboot-tools",
       author = "Andrew Andrianov",
       author_email = "andrew@ncrmnt.org",
       license = "GPL",
       platforms = "any",
       )