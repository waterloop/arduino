cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/avr-toolchain.cmake)

project(arduino C CXX ASM)

set(ARDUINO_PATH /usr/share/arduino/hardware/archlinux-arduino/avr)
set(USER_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

set(ARDUINO_CORE ${ARDUINO_PATH}/cores/arduino)
set(ARDUINO_LIBS ${ARDUINO_PATH}/libraries)
set(USER_LIBS ${/}/libraries)

add_definitions(-DF_CPU=16000000L -DARDUINO=10809 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR)

set(CMAKE_ASM_FLAGS "-g -x assembler-with-cpp -flto -MMD -mmcu=atmega328p")
set(CMAKE_C_FLAGS "-g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p")
set(CMAKE_CXX_FLAGS "-g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -fno-devirtualize -fno-use-cxa-atexit -mmcu=atmega328p")

include_directories(${ARDUINO_CORE} ${ARDUINO_PATH}/variants/standard)

file(GLOB arduino_core_sources ${ARDUINO_CORE}/*.cpp ${ARDUINO_CORE}/*.c ${ARDUINO_CORE}/*.S)
add_library(arduino_core STATIC ${arduino_core_sources})

file(GLOB arduino_libraries ${ARDUINO_LIBS}/* ${USER_LIBRARY_PATH}/*)
foreach(arduino_library ${arduino_libraries})
	get_filename_component(arduino_library_name ${arduino_library} NAME)
	file(GLOB arduino_library_files
		${arduino_library}/src/*.cpp
		${arduino_library}/src/*.c
		${arduino_library}/src/*.S
		${arduino_library}/*.cpp
		${arduino_library}/*.c
		${arduino_library}/*.S
	)
	if(arduino_library_files)
		add_library(${arduino_library_name} STATIC ${arduino_library_files})
		target_link_libraries(${arduino_library_name} arduino_core m)
		list(APPEND arduino_library_names ${arduino_library_name})
	endif()
	include_directories(${arduino_library}/src ${arduino_library})
endforeach(arduino_library)

function(create_target target sources)
	add_executable(${target} ${sources})
	target_link_libraries(${target} arduino_core ${arduino_library_names} m)

	add_custom_command(
		TARGET ${target} 
		POST_BUILD
		COMMAND ${CMAKE_OBJCOPY} -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 ${target} ${target}.eep
		COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${target} ${target}.hex
	)
endfunction(create_target)

create_target(arduino1 src/arduino1.cpp)
create_target(arduino2 src/arduino2.cpp)