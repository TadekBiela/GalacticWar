set(PROJECT_NAME galacticwar)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(${PROJECT_NAME} main.cpp)

qt5_use_modules(${PROJECT_NAME} Core Widgets Gui)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)
