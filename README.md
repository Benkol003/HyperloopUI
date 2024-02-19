# HyperloopUI

As part of the the UoM Hyperloop society, this GUI is being developed to remotely monitor & control the hyperloop pod.

## Library Dependencies
You need Qt6 Core & Widgets installed; you can download qt [here](https://www.qt.io/download).

(Place in ./lib/ folder)
Required to install dependencies:  
- [libcurl](https://curl.se/download.html) Source archive - place at lib/curl/

then run bin/build.sh .

## Windows Specifics
bin/build.sh needs to be run from a qt developer terminal.  
Running **windeployqt** will install the DLL dependencies in the current folder so that the executable can be run outside of the qt terminal.