cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/avr-toolchain.cmake)

project(arduino C CXX ASM)

set(ARDUINO_PATH /usr/share/arduino/hardware/archlinux-arduino/avr)
set(ARDUINO_CORE ${ARDUINO_PATH}/cores/arduino)
set(ARDUINO_LIBS ${ARDUINO_PATH}/libraries)
set(USER_LIBS ${/}/libraries)

set(CMAKE_ASM_FLAGS "-g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10809 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR")

set(CMAKE_C_FLAGS "-g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10809 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR")

set(CMAKE_CXX_FLAGS "-g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10809 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -lm")

include_directories(${ARDUINO_CORE} ${ARDUINO_PATH}/variants/standard)

add_library(arduino_core STATIC 
	${ARDUINO_CORE}/abi.cpp
	${ARDUINO_CORE}/CDC.cpp
	${ARDUINO_CORE}/HardwareSerial.cpp
	${ARDUINO_CORE}/HardwareSerial0.cpp
	${ARDUINO_CORE}/HardwareSerial1.cpp
	${ARDUINO_CORE}/HardwareSerial2.cpp
	${ARDUINO_CORE}/HardwareSerial3.cpp
	${ARDUINO_CORE}/hooks.c
	${ARDUINO_CORE}/IPAddress.cpp
	${ARDUINO_CORE}/new.cpp
	${ARDUINO_CORE}/PluggableUSB.cpp
	${ARDUINO_CORE}/Print.cpp
	${ARDUINO_CORE}/Stream.cpp
	${ARDUINO_CORE}/Tone.cpp
	${ARDUINO_CORE}/USBCore.cpp
	${ARDUINO_CORE}/WInterrupts.c
	${ARDUINO_CORE}/wiring_analog.c
	${ARDUINO_CORE}/wiring.c
	${ARDUINO_CORE}/wiring_digital.c
	${ARDUINO_CORE}/wiring_pulse.c
	${ARDUINO_CORE}/wiring_shift.c
	${ARDUINO_CORE}/WMath.cpp
	${ARDUINO_CORE}/WString.cpp
	${ARDUINO_CORE}/wiring_pulse.S
	${ARDUINO_CORE}/main.cpp
)

add_library(arduino_SPI STATIC
	${ARDUINO_LIBS}/SPI/src/SPI.cpp
)
include_directories(${ARDUINO_LIBS}/SPI/src)


add_library(arduino_SPI STATIC
	${ARDUINO_LIBS}/SPI/src/SPI.cpp
)
include_directories(${ARDUINO_LIBS}/SPI/src)

function(create_target target sources)
	add_executable(${target} ${sources})
	target_link_libraries(${target} arduino_core arduino_SPI)

	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 ${target} ${target}.eep
		COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${target} ${target}.hex
	)
endfunction(create_target)

create_target(test src/test/test.cpp)
