# Enviroment Setup Instructions for STM32:
- Use WSL or Linux, Ubuntu 22.04 works well
- Install clangd, cmake, cmake-tools extensions in VSCode
- On Ubuntu, `apt-get install gcc-arm-none-eabi` to install compiler
- Disable Intellisense when asked
- For configuration, select top-level `CMakeLists.txt`
- When building, use the appropriate (arm-none-eabi) compiler
- You'll need to install [STLink](https://github.com/stlink-org/stlink) drivers to flash the binary. 
