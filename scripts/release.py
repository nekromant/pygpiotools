#!/usr/bin/python3

import os
import fileinput
import shutil

#This hacky scripts does automatic version bumping. 
#It really sucks, but gets the job done nevertheless
def increment_ver(version):
    version = version.split('.')
    version[2] = str(int(version[2]) + 1)
    return '.'.join(version)

os.system(f"pip3 install .")
import pygpiotools

oldversion = pygpiotools.__version__
newversion = increment_ver(pygpiotools.__version__)
print(f"Preparing for {newversion} release")

#os.exit(1)
#os.system(f"python3 scripts/update_readme.py > README.new")
#os.system(f"mv README.new README.md")

with fileinput.FileInput("pygpiotools/__init__.py", inplace=True, backup='.bak') as file:
    for line in file:
        print(line.replace(oldversion, newversion), end='')

os.system(f"pip3 install .")

os.system("git add README.md")
os.system("git add pygpiotools/__init__.py")
os.system(f'git commit -s -m \"v{newversion} release\"')
os.system(f'git tag v{newversion}')
os.system(f"git push origin master")
os.system(f"git push origin v{newversion}")

if os.access('dist',os.R_OK):
    shutil.rmtree('dist')
os.system("python3 setup.py sdist")
os.system("twine check dist/* && twine upload dist/* --verbose")

