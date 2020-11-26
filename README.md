# GalacticWar

### 1. Requirements

    Qt 5.12.6 (it includes cmake and make)
    GTest 1.10.0


### 2. Prepare project to build

  * To build you need install Qt in this path: \
      `C:/Qt/`

  * And GTest for Unit Tests in this path: \
      `C:/GTest/`

  * Clone repo: \
      `git clone https://github.com/TadekBiela/GalacticWar.git`

  * Create folder `build` in repo directory and enter it.


### 3. Build game on Windows

  * Run this commands combination to build game as galacticwar.exe file: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 app`

  * Game exe file is in `app/` folder. **Enjoy!**


### 4. Build and run Unit Tests on Windows

  * Run this commands combination to build Unit Tests as ut.exe file: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 buildut`

  * If you want run only one or part of UTs just use gtest_filter: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 buildut && tests/ut --gtest_filter="*ControlPlane*"`

  * If you want build and run Uts use this command: \
      ` cmake ../ -G "MSYS Makefiles" && make -j4 runut`
