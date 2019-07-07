cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER   C:/Qt/Tools/mingw730_32/bin/gcc.exe)
set(CMAKE_C_FLAGS      "-static")
set(CMAKE_CXX_COMPILER C:/Qt/Tools/mingw730_32/bin/g++.exe)
set(CMAKE_CXX_FLAGS    "-static")

project("Galacic War")
enable_testing()

add_subdirectory(app)
add_subdirectory(tests)
