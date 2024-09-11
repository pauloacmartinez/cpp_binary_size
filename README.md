# cpp_binary_size

This project has the object of collecting interesting C++ examples
that impact the resulting binary size of applications,
specially on bare metal microcontrollers.

Moreover, this project additionaly provides a build system
for comparing, flashing and emulating the generated firmwares.

## Dependencies
- CMake >= 3.22
- Ninja
- renode
- puncover
- openocd

## Supported boards
- STM32F4DISCOVERY Discovery kit

## Partially supported boards
- Arduino UNO R4 Minima
- SiFive HiFive1 Rev B

## Usage

Setup build enviroment

```bash
$ cmake --preset stm32f4-MinSizeRel
$ cd build/stm32f4-MinSizeRel
```

build and emulate firmware

```bash
$ ninja emulate_iostream
```

build and flash firmware to target board

```bash
$ ninja flash_iostream
```

build, flash and read experiment duration in microseconds

```bash
$ ninja read_timer_iostream
```
