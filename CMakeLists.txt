cmake_minimum_required(VERSION 2.8)

#hush, annoying warnings
if(POLICY CMP0017)
 cmake_policy(SET CMP0017 NEW)
endif(POLICY CMP0017)

project(LibEuroIntroduction)

enable_testing()

include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
include(${CMAKE_ROOT}/Modules/CheckIncludeFileCXX.cmake)
include(${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)

#control default install prefix
SET(LEI_INSTALL_PREFIX "/usr" CACHE PATH "Prefix prepended to
install directories")
SET(CMAKE_INSTALL_PREFIX "${LEI_INSTALL_PREFIX}" CACHE INTERNAL "Prefix
prepended to install directories" FORCE)

# The version number.
set (LEI_VERSION_MAJOR 1)
set (LEI_VERSION_MINOR 0)

#enables debug flags
SET(CMAKE_BUILD_TYPE relwithdebinfo)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} --std=gnu++11 -Wall -pthread -Og ${wxWidgets_DEFINITIONS}")

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g")

set(header_destination "include/eurointroduction")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS date_time system REQUIRED) 

include_directories(${Boost_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory("src")
add_subdirectory("TestEzLogger")
