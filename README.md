Teensy 3 (MK20DX256VLH7) Sample code
====================================

A sample code collection to be used for educational purpose.

- [Blink](https://github.com/nabilbendafi/Teensy/tree/master/blink)
- [Blink (freeRTOS)](https://github.com/nabilbendafi/Teensy/tree/master/blink_freeRTOS)
- [Morse](https://github.com/nabilbendafi/Teensy/tree/master/morse)
- [Tone Morse](https://github.com/nabilbendafi/Teensy/tree/master/morse_tone)

Compilation
-----------

All samples have been successfully built on GCC Toolchain under Linux

  * Install GCC cross compiler for ARM Cortex-A/R/M processors
  * Update git submodules
```bash
git clone https://github.com/nabilbendafi/Teensy
cd Teensy
git submodule update --init
```
  * Compile
```bash
cd <project>
make
```

Upload
------

After compilation, use [Teensy Loader](https://www.pjrc.com/teensy/loader.html) to upload .hex to Teensy 3.1
