set(PROJECT_NAME galacticwar)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia)

add_executable(${PROJECT_NAME} main.cpp
                               bulletmodel.hpp
                               bulletmodel.cpp
                               bullettype.hpp
                               definitions.hpp
                               enemyconfiguration.hpp
                               enemycontroller.hpp
                               enemycontroller.cpp
                               enemymodel.hpp
                               enemymodel.cpp
                               enemymodeltype1.hpp
                               enemymodeltype1.cpp
                               filemanager.hpp
                               filemanager.cpp
                               firefunctions.hpp
                               firefunctions.cpp
                               functions.hpp
                               functions.cpp
                               generalview.hpp
                               generalview.cpp
                               graphicsview.hpp
                               graphicsview.cpp
                               ifilemanager.hpp
                               irandomgenerator.hpp
                               levelcontroller.hpp
                               levelcontroller.cpp
                               levelmodel.hpp
                               levelmodel.cpp
                               menucontroller.hpp
                               menucontroller.cpp
                               menumodel.hpp
                               menumodel.cpp
                               playercontroller.hpp
                               playercontroller.cpp
                               playermodel.hpp
                               playermodel.cpp
                               randomgenerator.hpp
                               randomgenerator.cpp
                               rewardcontroller.hpp
                               rewardcontroller.cpp
                               rewardmodel.hpp
                               rewardmodel.cpp
                               rewardcoinmodel.hpp
                               rewardcoinmodel.cpp
                               rewardspecialmodel.hpp
                               rewardspecialmodel.cpp
                               rewardtypes.hpp
                               scorecontroller.hpp
                               scorecontroller.cpp
                               scoremodel.hpp
                               scoremodel.cpp
                               weapons.hpp
                               weapons.cpp
                               weapontype.hpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Multimedia)
