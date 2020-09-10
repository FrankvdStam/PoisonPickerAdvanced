# I target a recent cmake, it shouldn't be a problem on a dev machine
cmake_minimum_required(VERSION 3.11)

#set(CMAKE_VERBOSE_MAKEFILE on)

project(PoisonPickerAdvanced)
set(PROJECT_NAME PoisonPickerAdvanced)

include_directories("C:/Program Files (x86)/Arduino/hardware/tools/avr/avr/include")

#========================================================================================
#Toolchain
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  avr)
set(CMAKE_C_COMPILER        avr-gcc)
set(CMAKE_CXX_COMPILER      avr-g++)
set(AVR_OBJCOPY             avr-objcopy)
set(AVR_SIZE_TOOL           avr-size)
set(AVR_OBJDUMP             avr-objdump)

set(AVR_UPLOADTOOL          avrdude)
set(AVR_UPLOADTOOL_PORT     usb)
set(AVR_PROGRAMMER          avrispmkII)

#========================================================================================
#mcu
set(AVR_MCU atmega328p)

add_executable(
        ${PROJECT_NAME}.elf
        src/main.c
)

set_target_properties(
        ${PROJECT_NAME}.elf
        PROPERTIES
        COMPILE_FLAGS "-mmcu=${AVR_MCU}"
        LINK_FLAGS "-mmcu=${AVR_MCU} -Wl,--gc-sections -mrelax"
)

add_custom_command(
        #avrdude needs a hex file instead of an elf file. We can convert it with abr-objcopy
        OUTPUT ${PROJECT_NAME}.hex
        COMMAND
        ${AVR_OBJCOPY} -j.text -j.data -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
        COMMAND
        ${AVR_SIZE_TOOL} -C;--mcu=${AVR_MCU} ${PROJECT_NAME}.elf
        DEPENDS ${PROJECT_NAME}.elf
)

#upload not supported because WSL doesn't allow usb passthrough. Maybe with some ssh trickery or usb over ip it would be possible
#however this would create a highly configured build environment which I'm trying to avoid.
#add_custom_command(
#        COMMAND
#        ${AVR_UPLOADTOOL} -v -p atmega328p -c arduino -P COM3 -b 115200 -D -U flash:w:${PROJECT_NAME}.hex:i
#        DEPENDS ${PROJECT_NAME}.hex
#
#        #https://stackoverflow.com/questions/43347087/cmake-add-custom-command-without-output
#        COMMAND ${CMAKE_COMMAND} -E touch uploadfile.stamp
#        OUTPUT uploadfile.stamp
#)


#add_custom_command(
#        DEPENDS ${PROJECT_NAME}.hex
#        COMMAND
#        rm ${PROJECT_NAME}.hex ${PROJECT_NAME}.elf
#        COMMAND ${CMAKE_COMMAND} -E touch deletefile.stamp
#        OUTPUT deletefile.stamp
#)

add_custom_target(
        build ALL
        DEPENDS ${PROJECT_NAME}.hex)


