# IMPORTANT NOTE
This repository contains not fully setup code environment for use during the workshop.

For complete examples see my matching repository at https://github.com/misskacie/simple-pico-examples
which has fully setup CMAKE files.

### Setting up Pico SDK Workspace
In order to build the project you will need to run the following commands

- `cd [PATH_TO_REPO]`
- `mkdir build`
- `cd build`
- `cmake ..; make`

There will now be a uf2 file within the build folder that can be flashed to the pico.

To flash the uf2 file to the pico you can hold down the boot button on the pico and then plug it in which will mount it like a storage device, then you copy the uf2 file onto the mounted storage device. Alternatively you can use pico-tool from the Raspberry Pi Foundation. 

You can run `cmake..; make; sudo picotool load -F [filetoflash].uf2; sudo picotool reboot` from the build folder to automatically build and copy it over, if it fails you will need to manually put it into bootsel mode as above.

### Installing picotool
First do
- `git clone https://github.com/raspberrypi/picotool`
- `cd picotool`

To avoid having to set a path variable for the pico-sdk you can edit `CMakeLists.txt` and add the following below first line (`cmake_minimum_required()`)
```
set(PICO_SDK_FETCH_FROM_GIT 1)
include(pico_sdk_import.cmake)
```

Then copy the file `pico_sdk_import.cmake` from this repository into the picotool folder. Alternatively you can setup pico-sdk path variable. 
Now run:
- `mkdir build`
- `cmake ..`
- `make install`


### Serial Ports on Linux
In order to access the serial ports we must allow access to the files. The file is located at /dev/ttyACM0, /dev/ttyACM1 ect.
- To do this we add a udev rule for each file
- Create a file ttyACM0.rules containing `KERNEL=="ttyACM0", MODE="0666"` at /etc/udev/rules.d/ttyACM0.rules

To do that we run the following commands:
- `echo 'KERNEL=="ttyACM0", MODE="0666"' | sudo tee /etc/udev/rules.d/ttyACM0.rules`
- `sudo udevadm control --reload-rules` 
- `sudo udevadm trigger`


### CMake Notes
The files `pico_sdk_import.cmake` and `FreeRTOS_import.cmake` depend on `FetchContent_Populate()` which was deprecated in new versions of CMake. When the pico-sdk and FreeRTOS_Kernel start using new CMake versions, these calls will need to be replaced with `FetchContent_MakeAvailable()` however this is not a one to one switch.
