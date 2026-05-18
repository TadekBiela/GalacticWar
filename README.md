# GalacticWar

### 1. Requirements
  * [CMake](https://cmake.org/download/){:target="_blank" rel="noopener"}
  * [Git Bash](https://git-scm.com/install/windows){:target="_blank" rel="noopener"}
  * [Qt 5.12.6](http://download.qt.io/archive/qt/5.12/5.12.6/){:target="_blank" rel="noopener"}
  * [googletest](https://github.com/google/googletest){:target="_blank" rel="noopener"}
  * [GraphicsGale](https://graphicsgale.com/us/download.html){:target="_blank" rel="noopener"} as graphics editor (not necessary to build)
  * [Python3](https://www.python.org/downloads/){:target="_blank" rel="noopener"} (not necessary to build)

### 2. Prepare project to build
  * To build you need install **Qt** in this path: \
      `C:/Qt/`
  * And **googletest** for unit tests in this path: \
      `C:/googletest/`
  * Run **Git Bash** and clone repo: \
      `git clone https://github.com/TadekBiela/GalacticWar.git`
  * Setup environment in repo directory( creates new shell, no changes in system needed): \
      `./build-msys.sh`
  * Now project is ready to build!

### 3. Build game on Windows
  * Run this commands combination to build game as galacticwar.exe file in Git Bash console: \
      `cmake --build . --target app --parallel 4`
  * Game exe file is in `app/` folder. **Enjoy!**

### 4. Build and run Unit Tests on Windows
  * Run this commands combination to build Unit Tests as ut.exe file: \
      `cmake --build . --target buildut --parallel 4`
  * If you want run only one or part of UTs just use gtest_filter: \
      `cmake --build . --target buildut --parallel 4 && tests/ut --gtest_filter="*ControlPlane*"`
  * If you want build and run Uts use this command: \
      `cmake --build . --target runut --parallel 4`

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
