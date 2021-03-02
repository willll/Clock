
cmake_minimum_required(VERSION 2.8.9)
project (Clock)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_VERBOSE_MAKEFILE ON)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED)

add_executable(Clock Clock.cpp)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/src) 
include_directories(${WIRINGPI_INCLUDE_DIRS}) 
include_directories(/home/pi/Freenove_Ultimate_Starter_Kit_for_Raspberry_Pi/Libs/C-Libs/ADCDevice)

# Link against libraries
target_link_libraries(
    Clock
    ${WIRINGPI_LIBRARIES}
    Threads::Threads
    m
    "${CMAKE_SOURCE_DIR}/lib/libADCDevice.so"
) 


