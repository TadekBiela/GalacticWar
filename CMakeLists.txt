cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++17")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(CMAKE_C_COMPILER   C:/Qt/Tools/mingw730_32/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/Qt/Tools/mingw730_32/bin/g++.exe)

project("Galacic War")
enable_testing()

add_subdirectory(app)
add_subdirectory(tests)
