# Raspberry Pi Pico RP2040 BOOTSEL reboot example

## Introduction

This github repo is a sample program to use the BOOTSEL button as a two-stage reboot button for the Pico RP2040.

Pressing the button and releasing it will reboot the Pico RP2040 and start running your application again.

Pressing and holding the button will reboot the Pico RP2040 and go into USB mass storage mode so you can upload a new application.

I have written this sample to help others from damaging the fragile Micro USB connector on the Pico RP2040 board.

## Analysis

This sample application is a hello-world style application, it will print "Hello World" to the USB-CDC UART and flash the LED at 1 Hertz in a non-blocking fashion by making use of the on-board timer.

This application utilises the RP2040 watchdog to perform the actual reset so that we can benefit from two-stage rebooting.

## Warning

This code utilises low-level functions to tap into the BOOTSEL button that can stall (and potentially disrupt) code that utilises the on-board flash storage (ie. datalogging). This code also briefly disables interrupts whilst it checks the state of the BOOTSEL button.

Although this code executes quickly there is always the possibility your application may miss an interrupt or not read or write to flash.

**Use with caution and test thoroughly!**

## Installation

This code was written with the intention of being compiled on a Linux system (in my case, Ubuntu 20.04).

It expects that the `pico-sdk` folder is located in the parent folder above this (or the parent folder above that). Examples of this are as follows...

#### SDK located in parent folder
```
├── rp2040-bootsel-reboot-example
│   ├── .gitignore
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── bootsel-reboot.cpp
│   ├── bootsel-reboot.hpp
│   ├── build.sh
│   └── rp2040-bootsel-reboot-example.cpp
└── pico-sdk
    ├── CMakeLists.txt
    ├── LICENSE.TXT
    ├── README.md
    └── ... more files
```

#### Your code in a projects folder
```
├── my-projects
│   └── rp2040-bootsel-reboot-example
│       ├── .gitignore
│       ├── CMakeLists.txt
│       ├── README.md
│       ├── bootsel-reboot.cpp
│       ├── bootsel-reboot.hpp
│       ├── build.sh
│       └── rp2040-bootsel-reboot-example.cpp
└── pico-sdk
    ├── CMakeLists.txt
    ├── LICENSE.TXT
    ├── README.md
    └── ... more files
```

To compile, check out the code and run the build shell script...

```bash
git clone git@github.com:jasongaunt/rp2040-bootsel-reboot-example.git
cd rp2040-bootsel-reboot-example/
./build.sh
```

The code should then build (usually in under 30 seconds, [YMMV](https://dictionary.cambridge.org/dictionary/english/ymmv)). 


Once built, in the `build/` folder you should find `rp2040-bootsel-reboot-example.uf2` - copy this to your Pico RP2040 and enjoy

## Sample Usage

When this sample application is uploaded to your Pico RP2040 it will print "Hello World" to the USB-CDC Serial device and then start flashing the on-board LED at a rate of 1 Hertz.

Press the BOOTSEL button and release immediately and the Pico RP2040 will reboot and start running the application again.

Press and hold the BOOTSEL button and it will reboot into USB mass storage mode so you can upload a new application.

## Using in your own application

1. In your `CMakeLists.txt` make sure to add `bootsel-reboot.cpp` to the `add_executable()` block.

2. At the top of your application add `#include "bootsel-reboot.hpp"`

3. At the start of your application entry point (usually the `int main()` function) add `arm_watchdog();` after `stdio_init_all();`

4. In your application main loop call `check_bootsel_button();` frequently (ideally every 100 ms or less)

**Warning:** If `check_bootsel_button();` isn't called every 1000 ms or less the watchdog will reboot the Pico RP2040!

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Contributors
* Jason Gaunt - Initial Application
* Raspberry Pi team - SDK and code samples that made this possible

## License
[MIT](https://choosealicense.com/licenses/mit/)