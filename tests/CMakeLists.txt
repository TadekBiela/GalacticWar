add_custom_target(buildut)
add_custom_target(runut
                  COMMAND exec ${CMAKE_BINARY_DIR}/tests/ut.exe)
set(PROJECT_NAME ut)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(STD_LIB C:/Qt/Tools/mingw730_32/bin/libstdc++-6.dll)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia)
find_package(Qt5Test REQUIRED)

add_subdirectory("C:/GTest" ${CMAKE_BINARY_DIR}/gtest)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp
                               ../app/animationeffectmodel.hpp
                               ../app/animationeffectmodel.cpp
                               ../app/animationplaneview.hpp
                               ../app/animationplaneview.cpp
                               ../app/barview.hpp
                               ../app/barview.cpp
                               ../app/bulletmodel.hpp
                               ../app/bulletmodel.cpp
                               ../app/controlplane.hpp
                               ../app/controlplane.cpp
                               ../app/definitions.hpp
                               ../app/enemyconfiguration.hpp
                               ../app/enemycontroller.hpp
                               ../app/enemycontroller.cpp
                               ../app/enemymodel.hpp
                               ../app/enemymodel.cpp
                               ../app/enemymodeltype1.hpp
                               ../app/enemymodeltype1.cpp
                               ../app/enemymodeltype2.hpp
                               ../app/enemymodeltype2.cpp
                               ../app/enemymodeltype3.hpp
                               ../app/enemymodeltype3.cpp
                               ../app/enemymodeltype4.hpp
                               ../app/enemymodeltype4.cpp
                               ../app/enemymodeltype5.hpp
                               ../app/enemymodeltype5.cpp
                               ../app/enemymodeltype6.hpp
                               ../app/enemymodeltype6.cpp
                               ../app/enemyturret.hpp
                               ../app/enemyturret.cpp
                               ../app/firefunctions.hpp
                               ../app/firefunctions.cpp
                               ../app/filemanager.hpp
                               ../app/filemanager.cpp
                               ../app/functions.hpp
                               ../app/functions.cpp
                               ../app/gameobject.hpp
                               ../app/gameobject.cpp
                               ../app/gameplayview.hpp
                               ../app/gameplayview.cpp
                               ../app/graphicsview.hpp
                               ../app/graphicsview.cpp
                               ../app/healthcontroller.hpp
                               ../app/healthcontroller.cpp
                               ../app/healthmodel.hpp
                               ../app/healthmodel.cpp
                               ../app/ifilemanager.hpp
                               ../app/iimagestorage.hpp
                               ../app/iimagestorage.cpp
                               ../app/iinterfaceview.hpp
                               ../app/iinterfaceview.cpp
                               ../app/isoundstorage.hpp
                               ../app/isoundstorage.cpp
                               ../app/imagestorage.hpp
                               ../app/imagestorage.cpp
                               ../app/irandomgenerator.hpp
                               ../app/label.hpp
                               ../app/label.cpp
                               ../app/labelview.hpp
                               ../app/labelview.cpp
                               ../app/levelmodel.hpp
                               ../app/levelmodel.cpp
                               ../app/menucontroller.hpp
                               ../app/menucontroller.cpp
                               ../app/menumodel.hpp
                               ../app/menumodel.cpp
                               ../app/menuview.hpp
                               ../app/menuview.cpp
                               ../app/playercontroller.hpp
                               ../app/playercontroller.cpp
                               ../app/playermodel.hpp
                               ../app/playermodel.cpp
                               ../app/pushbutton.hpp
                               ../app/pushbutton.cpp
                               ../app/randomgenerator.hpp
                               ../app/randomgenerator.cpp
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
                               stubs/barviewstub.hpp
                               stubs/filemanagerstub.hpp
                               stubs/imagestoragestub.hpp
                               stubs/randomgeneratorstub.hpp
                               stubs/soundstoragestub.hpp
                               mocks/filemanagermock.hpp
                               utdefinitions.hpp
                               animationeffectmodeltests.cpp
                               bulletmodeltests.cpp
                               controlplanetests.cpp
                               enemycontrollertests.cpp
                               enemymodeltests.cpp
                               enemymodeltype1tests.cpp
                               enemymodeltype2tests.cpp
                               enemymodeltype6tests.cpp
                               enemyturrettests.cpp
                               functionstests.cpp
                               healthcontrollertests.cpp
                               healthmodeltests.cpp
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

target_link_libraries(${PROJECT_NAME} gtest gtest_main gmock Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Multimedia Qt5::Test)
add_test(NAME bulletmodeltests COMMAND ${PROJECT_NAME})

file(COPY        ${STD_LIB}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
 add_dependencies(buildut ${PROJECT_NAME})
 add_dependencies(runut ${PROJECT_NAME})
