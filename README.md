# GalacticWar

## 1. Requirements
  * CMake [link](https://cmake.org/download/)
  * Python3 [link](https://www.python.org/downloads/)
  * Qt 5.12.6 [link](http://download.qt.io/archive/qt/5.12/5.12.6/)
  * GTest 1.10.0 [link](https://github.com/google/googletest)
  * GraphicsGale as graphics editor [link](https://graphicsgale.com/us/download.html)  (not nessesary to build)


## 2. Windows development
### 2.1. Prepare project to build

  * To build you need install Qt in this path: \
      `C:/Qt/`

  * Add Qt, C and C++ compilers dirs to PATH env variable: \
    on Windows: \
      `C:\Qt\Qt5.12.6\5.12.6\mingw73_32\bin` \
      `C:\Qt\Qt5.12.6\Tools\mingw730_32\bin`

  * Jump into `C:\Qt\Qt5.12.6\Tools\mingw730_32\bin` and copy mingw32-make.exe as make.exe: \
      `cp mingw32-make.exe make.exe`

  * And GTest for Unit Tests in this path: \
      `C:/googletest/`

  * Clone repo: \
      `git clone https://github.com/TadekBiela/GalacticWar.git`

  * Create folder `build` in repo directory and enter it in Git Bash console: \
      `mkdir build && cd build`


### 2.2. Build game

  * Run this commands combination to build game as galacticwar.exe file in Git Bash console: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 app`

  * Game `galacticwar.exe` file is in `app/` folder. **Enjoy!**


### 2.3. Build and run Unit Tests

  * Run this commands combination to build Unit Tests as ut.exe file: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 buildut`

  * If you want run only one or part of UTs just use gtest_filter: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 buildut && tests/ut --gtest_filter="*ControlPlane*"`

  * If you want build and run Uts use this command: \
      ` cmake ../ -G "MSYS Makefiles" && make -j4 runut`


## 3. Linux development (Ubuntu)
### 3.1. Prepare project to build

  * To build you need install Qt in this path: \
      `/opt/Qt5.12.6/`

  * And GTest for Unit Tests in this path: \
      `/opt/googletest/`

  * Install nessesary packages: \
      `sudo apt install gcc g++ mesa-common-dev libglu1-mesa-dev`

  * Clone repo: \
      `git clone https://github.com/TadekBiela/GalacticWar.git`

  * Create folder `build` in repo directory and enter it in Git Bash console: \
      `mkdir build && cd build`


### 3.2. Build game

  * Run this commands combination to build game as galacticwar.exe file in Git Bash console: \
      `cmake ../ -G "Unix Makefiles" && make -j4 app`

  * Game `galacticwar` file is in `app/` folder. **Enjoy!**


### 3.3. Build and run Unit Tests

  * Run this commands combination to build Unit Tests as ut.exe file: \
      `cmake ../ -G "Unix Makefiles" && make -j4 buildut`

  * If you want run only one or part of UTs just use gtest_filter: \
      `cmake ../ -G "Unix Makefiles" && make -j4 buildut && tests/ut --gtest_filter="*ControlPlane*"`

  * If you want build and run Uts use this command: \
      ` cmake ../ -G "Unix Makefiles" && make -j4 runut`
