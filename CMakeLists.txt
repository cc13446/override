cmake_minimum_required(VERSION 3.21)
project(override)

set(CMAKE_CXX_STANDARD 14)

add_executable(override test/main.cpp ClassWrapper.cpp ClassWrapper.h test/TestClass.cpp test/TestClass.h Override.cpp Override.h SafeChecker.h SafeChecker.cpp)
