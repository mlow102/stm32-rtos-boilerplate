# STM32 FreeRTOS Boilerplate
Boilerplate for programming STM32 boards in C++, using cmake

## Enviroment Setup Instructions:
- Use WSL or Linux, Ubuntu 22.04 works well
- Install clangd, cmake, cmake-tools extensions in VSCode
- On Ubuntu, `apt-get install gcc-arm-none-eabi` to install compiler
- Disable Intellisense when asked
- For configuration, select top-level `CMakeLists.txt`
- When building, use the appropriate (arm-none-eabi) compiler
- You'll need to install [STLink](https://github.com/stlink-org/stlink) drivers to flash the binary. 
