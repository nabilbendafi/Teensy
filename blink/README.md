Teensy 3 (MK20DX256VLH7) LED blink demo
=======================================

Libraries
---------

This minimal example uses no external library:
no [MBED](https://www.mbed.com/en/) SDK, no Arduino, no Teensyduino

Though follows files are borrowed from [MBED](https://www.mbed.com/en/) project
- Device specific configuration files:
  * [system_MK20DX256.c](https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/system_MK20DX256.c) and [system_MK20DX256.h](https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/system_MK20DX256.h)
- CMSIS Peripheral Access Layer header:
  * [MK20DX256.h](https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/MK20DX256.h)
- Linker script : 
  * [MK20DX256.ld](https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/TOOLCHAIN_GCC_ARM/MK20DX256.ld)
- Startup file for Cortex-M4 devices:
  * [startup_MK20DX256.S](https://github.com/mbedmicro/mbed/blob/master/libraries/mbed/targets/cmsis/TARGET_Freescale/TARGET_K20XX/TARGET_TEENSY3_1/TOOLCHAIN_GCC_ARM/startup_MK20DX256.S)

And Makefile is coming from [MBED](https://www.mbed.com/en/) GCC Makefile templates

Pinouts
-------

Teensy LED connected on port 13 is connected to MK20DX256VLH7 Pin 50

![Teensy 3.x schematics](https://github.com/nabilbendafi/Teensy/blob/master/blink/schematic3.gif)

(Source: [PJRC](https://www.pjrc.com/teensy/schematic3.gif))


| 64 LQFP _QFN | Pin Name | Default | ALT0 |  ALT1 |  ALT2  |    ALT3   |   ALT4  |  ALT5 |   ALT6 |
|----|----------|---------|------|-------|--------|-----------|---------|-------|--------|
| 50 | PTC5/LLWU_P9    |DISABLED |      |PTC5/LLWU_P9  |SPI0_SCK|LPTMR0_ALT2|I2S0_RXD0|FB_AD10|CMP0_OUT|

(Source: K20 Sub-Family Reference Manual
10.3.1 K20 Signal Multiplexing and Pin Assignments)

Code explenation
---------------
Before using any GPIO pin (here PTC refers to Port C), clock gate need to be enabled by setting PORTC field (bit 11) of SIM_SCGC5 register.
```c
SIM->SCGC5 = SIM_SCGC5_PORTC_MASK;
```

To make pin 50 run as *GPIO* we need to select Alternative 1 for MUX field (bit	10-8) of PORTC_PCR5 register
```c
PORTC->PCR[5] = PORT_PCR_MUX(1);
```

We just toggle the logic state by writting bit 5 of GPIOC_PTOR register
```c
PTC->PTOR = (1<<5);
```
Alternativly switching the led on and off

```c
SysTick_Config(SystemCoreClock / 1000) != 0
```
will generate an interrupt every 1ms and call *SysTick_Handler* which only increments *msTicks*
```c
volatile unsigned long msTicks
```
used for our *wait* function. **volatile**,  so the empty loop is not optimised (ie removed) by the compilator.

Makefile
-----------

Option ```--specs=nosys.specs``` is used and no C libraries linked to make the .hex files the smallest

Compilation
-----------

gcc version 4.9.3 20150529 (release) (GNU Tools for ARM Embedded Processors) 

```
cd blink
make
```
