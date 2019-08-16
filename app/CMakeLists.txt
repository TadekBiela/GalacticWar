set(PROJECT_NAME galacticwar)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia)

add_executable(${PROJECT_NAME} main.cpp
                               bulletmodel.cpp
                               enemymodel.cpp
                               enemymodeltype1.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Multimedia)
