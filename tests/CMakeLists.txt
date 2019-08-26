set(PROJECT_NAME ut)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(STD_LIB C:/Qt/Tools/mingw730_32/bin/libstdc++-6.dll)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia)
find_package(Qt5Test REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
                               bulletmodeltests.cpp
                               enemymodeltests.cpp
                               enemymodeltype1tests.cpp
                               randomgeneratorstub.cpp
                               ../app/bulletmodel.cpp
                               ../app/enemymodel.cpp
                               ../app/enemymodeltype1.cpp
                               ../app/functions.cpp)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

target_link_libraries(${PROJECT_NAME} gtest Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Multimedia Qt5::Test)
add_test(NAME bulletmodeltests COMMAND ${PROJECT_NAME})

file(COPY  ${STD_LIB}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
