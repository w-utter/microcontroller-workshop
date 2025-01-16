# IMPORTANT NOTE
This repository contains not fully setup code environment for use during the workshop.

For complete examples see my matching repository at https://github.com/misskacie/simple-pico-examples
which has fully setup CMAKE files.

### Building & Flashing with the Pico SDK
In order to build the project you will need to run the following commands

- `cd [PATH_TO_REPO]`
- `mkdir build`
- `cd build`
- `cmake ..; make`

There will now be a uf2 file within `[PATH_TO_REPO]/build` that can be flashed to the pico.

To flash the compiled uf2 file, first plug in and hold the boot button. This will mount it like a storage device. There are then 2 options to flash the uf2 file:

- copy the file into the newly mounted device.
- run `sudo picotool load -F [FILE_TO_FLASH].uf2; sudo picotool reboot` within `[PATH_TO_REPO]/build`

NOTE: using picotool automatically puts the device into bootsel mode so the boot button does not typically need to be held down unless there are issues flashing the device.

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

### Attribution
Some examples taken or adapted from https://github.com/raspberrypi/pico-examples
