set(PROJECT_NAME ut)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(STD_LIB C:/Qt/Tools/mingw730_32/bin/libstdc++-6.dll)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia)
find_package(Qt5Test REQUIRED)

add_subdirectory("C:/GTest" ${CMAKE_BINARY_DIR}/gtest)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp
                               ../app/bulletmodel.hpp
                               ../app/bulletmodel.cpp
                               ../app/bullettype.hpp
                               ../app/definitions.hpp
                               ../app/enemyconfiguration.hpp
                               ../app/enemycontroller.hpp
                               ../app/enemycontroller.cpp
                               ../app/enemymodel.hpp
                               ../app/enemymodel.cpp
                               ../app/enemymodeltype1.hpp
                               ../app/enemymodeltype1.cpp
                               ../app/firefunctions.hpp
                               ../app/firefunctions.cpp
                               ../app/functions.hpp
                               ../app/functions.cpp
                               ../app/gameobject.hpp
                               ../app/gameobject.cpp
                               ../app/generalview.hpp
                               ../app/generalview.cpp
                               ../app/graphicsview.hpp
                               ../app/graphicsview.cpp
                               ../app/ifilemanager.hpp
                               ../app/irandomgenerator.hpp
                               ../app/levelcontroller.hpp
                               ../app/levelcontroller.cpp
                               ../app/levelmodel.hpp
                               ../app/levelmodel.cpp
                               ../app/menucontroller.hpp
                               ../app/menucontroller.cpp
                               ../app/menumodel.hpp
                               ../app/menumodel.cpp
                               ../app/playercontroller.hpp
                               ../app/playercontroller.cpp
                               ../app/playermodel.hpp
                               ../app/playermodel.cpp
                               ../app/rewardcontroller.hpp
                               ../app/rewardcontroller.cpp
                               ../app/rewardmodel.hpp
                               ../app/rewardmodel.cpp
                               ../app/rewardcoinmodel.hpp
                               ../app/rewardcoinmodel.cpp
                               ../app/rewardspecialmodel.hpp
                               ../app/rewardspecialmodel.cpp
                               ../app/rewardtypes.hpp
                               ../app/scorecontroller.hpp
                               ../app/scorecontroller.cpp
                               ../app/scoremodel.hpp
                               ../app/scoremodel.cpp
                               ../app/soundeffectmodel.hpp
                               ../app/soundeffectmodel.cpp
                               ../app/soundstorage.hpp
                               ../app/soundstorage.cpp
                               ../app/weapons.hpp
                               ../app/weapons.cpp
                               ../app/weapontype.hpp
                               stubs/filemanagerstub.hpp
                               stubs/randomgeneratorstub.hpp
                               mocks/filemanagermock.hpp
                               bulletmodeltests.cpp
                               utdefinitions.hpp
                               enemycontrollertests.cpp
                               enemymodeltests.cpp
                               enemymodeltype1tests.cpp
                               generalviewtests.cpp
                               levelcontrollertests.cpp
                               levelmodeltests.cpp
                               menucontrollertests.cpp
                               menumodeltests.cpp
                               playercontrollertests.cpp
                               playermodeltests.cpp
                               rewardcontrollertests.cpp
                               rewardmodeltests.cpp
                               rewardcoinmodeltests.cpp
                               rewardspecialmodeltests.cpp
                               scorecontrollertests.cpp
                               scoremodeltests.cpp
                               soundeffectmodeltests.cpp)

target_link_libraries(${PROJECT_NAME} gtest gtest_main Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Multimedia Qt5::Test)
add_test(NAME bulletmodeltests COMMAND ${PROJECT_NAME})

file(COPY        ${STD_LIB}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
