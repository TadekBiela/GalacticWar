# GalacticWar

### 1. Requirements
  * CMake [link](https://cmake.org/download/)
  * Python3 [link](https://www.python.org/downloads/)
  * Qt 5.12.6 [link](http://download.qt.io/archive/qt/5.12/5.12.6/)
  * GTest 1.10.0 [link](https://github.com/google/googletest)
  * GraphicsGale as graphics editor [link](https://graphicsgale.com/us/download.html)  (not nessesary to build)


### 2. Prepare project to build

  * To build you need install Qt in this path: \
      `C:/Qt/`

  * Add Qt, C and C++ compilers dirs to PATH env variable: \
    on Windows: \
      `C:\Qt\Qt5.12.6\5.12.6\mingw73_32\bin` \
      `C:\Qt\Qt5.12.6\Tools\mingw730_32\bin`

  * Jump into `C:\Qt\Qt5.12.6\Tools\mingw730_32\bin` and copy mingw32-make.exe as make.exe: \
      `cp mingw32-make.exe make.exe`

  * And GTest for Unit Tests in this path: \
      `C:/GTest/`

  * Clone repo: \
      `git clone https://github.com/TadekBiela/GalacticWar.git`

  * Create folder `build` in repo directory and enter it in Git Bash console: \
      `mkdir build && cd build`


### 3. Build game on Windows

  * Run this commands combination to build game as galacticwar.exe file in Git Bash console: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 app`

  * Game exe file is in `app/` folder. **Enjoy!**


### 4. Build and run Unit Tests on Windows

  * Run this commands combination to build Unit Tests as ut.exe file: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 buildut`

  * If you want run only one or part of UTs just use gtest_filter: \
      `cmake ../ -G "MSYS Makefiles" && make -j4 buildut && tests/ut --gtest_filter="*ControlPlane*"`

  * If you want build and run Uts use this command: \
      ` cmake ../ -G "MSYS Makefiles" && make -j4 runut`

## Security Note

### Why do I see a Windows SmartScreen warning?

When attempting to run the galacticwarsetup.exe installer, you may encounter a message stating: "Windows protected your PC" along with an "Unknown Publisher" warning.

Rest assured – this is a standard aspect of distributing open-source software:

* No Digital Signature: As a hobbyist open-source project, GalacticWar does not have a paid Code Signing Certificate, which typically costs around $400 per year.
* Transparency: The entire source code for the game and the installer script (.iss) are publicly available in this repository. Anyone can verify exactly how the application is built and what it does.
* Detailed Metadata: While the file is not digitally signed, it has been prepared with professional care. You can find correct version and author information in the file properties.

### How to run the game?

To proceed with the installation, click "More info".

Then, click the "Run anyway" button.

I believe in technical honesty and quality. Instead of ignoring this hurdle, I prefer to provide a clear and direct explanation to my users.
