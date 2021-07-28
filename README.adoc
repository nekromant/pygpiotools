:toc:
:toc-placement!:

Python tools to control gpio pins on pl2303, cp210x and (maybe) others.

image::https://ci.appveyor.com/api/projects/status/github/nekromant/pygpiotools[]

toc::[]

= PyGPIOTools 

== Introduction

Remember those cheap usb-to-uart modules that have gpio pins? Want to control them from your app in 
linux, windows and (hopefully) mac. Old pl2303gpio doesn't get the job done? 
This library aims to fix the problems.

== Supported hardware

.Hardware support matrix
[width="100%", options="header"]
|=========================================================
|Chip | Number of GPIOs |Driver | Windows | Linux | Mac

| PL2303HXA    | 2 | pl2303 | Yes | Yes | ???
| CP210x       | 8 | cp230x | WIP | WIP | ??? 

|=========================================================

== Installation
=== Requirements

Any recent python 3.x. 3.7 and above should be good. Please report you successes so that I can add the information here.

Linux (and mac, perhaps) versions need pyusb. 
Windows versions need Visual Studio Build Tools installed. It's a huge download, but it's needed. Grab it at 
https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2017[Microsoft download site].


=== Building Installing python module

----
pip install .
----

This library will be uploaded to pypy once inital work and porting code from pl2303gpio is done.

----
pip install pygpiotools
----

== Using commandline tool

TODO

== API and examples 

TODO

== Authors

Andrew 'Necromant' Andrianov <andrew@ncrmnt.org> - pl2303/cp2102 gpio code and initial implementation

== License

TBD