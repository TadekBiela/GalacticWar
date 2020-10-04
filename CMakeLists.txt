cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/app/images/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app/images)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/app/images/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests/images)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/app/sounds/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app/sounds)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/app/sounds/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests/sounds)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/app/fonts/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app/fonts)

project("Galacic War")
enable_testing()

add_subdirectory(app)
add_subdirectory(tests)
