cmake_minimum_required(VERSION 3.16)
add_subdirectory(cmake-helpers)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake-helpers/cmake/stm32_gcc.cmake)

project(stm32-tracker-controller C CXX ASM)

stm32_fetch_cmsis(F4)
stm32_fetch_hal(F4)

find_package(HAL COMPONENTS STM32F4 REQUIRED)
find_package(CMSIS COMPONENTS STM32F4 REQUIRED)
find_package(FreeRTOS COMPONENTS ARM_CM4F REQUIRED)

add_executable(stm32-tracker-controller main.cpp stm32f4xx_hal_conf.h)

target_link_libraries(stm32-tracker-controller
        HAL::STM32::F4::RCC
        HAL::STM32::F4::GPIO
        HAL::STM32::F4::CORTEX
        HAL::STM32::F4::I2C
        HAL::STM32::F4::SPI
        CMSIS::STM32::F410CB
        STM32::NoSys
        FreeRTOS::Timers
        FreeRTOS::Heap::4
        FreeRTOS::ARM_CM4F
    )

Set(LINK_OPTIONS -mcpu=cortex-m4 -mfpu=vfpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs --specs=nosys.specs -Wl,-Map=stm32-tracker-controller.map,--cref -Wl,--gc-sections -Wl,--print-memory-usage -ldaisy -lc -lm -lnosys)
Set(CFLAGS -mcpu=cortex-m4 -mthumb -mfpu=vfpv4-d16 -mfloat-abi=hard -O2 -Wall -Wno-missing-attributes -fasm -fdata-sections -ffunction-sections -Wno-stringop-overflow -g -ggdb -mthumb-interwork)
Set(CPPFLAGS  -mcpu=cortex-m4 -mthumb -mfpu=vfpv4-d16 -mfloat-abi=hard -O2 -Wall -Wno-missing-attributes -fasm -fdata-sections -ffunction-sections -Wno-stringop-overflow -g -ggdb -fno-exceptions -fasm -finline -finline-functions-called-once -fshort-enums -fno-move-loop-invariants -fno-unwind-tables -fno-rtti -Wno-register -mthumb-interwork)
Set(ASM_FLAGS  -mcpu=cortex-m4 -mthumb -mfpu=vfpv4-d16 -mfloat-abi=hard -O2  -Wall -fdata-sections -ffunction-sections -mthumb-interwork)

target_link_options(stm32-tracker-controller INTERFACE ${LINK_OPTIONS})
target_compile_options(stm32-tracker-controller PUBLIC
    $<$<COMPILE_LANGUAGE:C>: ${CFLAGS}>
    $<$<COMPILE_LANGUAGE:CXX>:${CPPFLAGS}>
    $<$<COMPILE_LANGUAGE:ASM>: ${ASM_FLAGS}>
)

# Update this to set the device target:
target_compile_definitions(stm32-tracker-controller PUBLIC 
    -DCORE_CM4  
    #-DSTM32F410xx 
    #-DSTM32F410Cx
    #-DSTM32F410CB
    -DSTM32F411xx
    -DSTM32F410Rx
    -DSTM32F410RE
    -DARM_MATH_CM4 
    -Dflash_layout 
    -DHSE_VALUE=16000000 
    -DUSE_HAL_DRIVER 
    -DUSE_FULL_LL_DRIVER 
    -DDATA_IN_D2_SRAM 
    -DUSE_ARM_DSP
)

stm32_generate_binary_file(stm32-tracker-controller)
stm32_print_size_of_target(stm32-tracker-controller)