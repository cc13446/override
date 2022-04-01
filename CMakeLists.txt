cmake_minimum_required(VERSION 3.21)
project(override)

set(CMAKE_CXX_STANDARD 14)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
ADD_DEFINITIONS(-D _DEBUG)
ENDIF()

add_executable(override test/main.cpp ClassWrapper.cpp ClassWrapper.h test/TestClass.cpp test/TestClass.h Override.cpp Override.h SafeChecker.h SafeChecker.cpp)
