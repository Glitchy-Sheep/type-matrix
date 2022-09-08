## Table of contents:

- [Building process](#building-process)
  - [Windows (mingw or visual studio)](#windows-mingw-or-visual-studio)
  - [Linux (gcc)](#linux-gcc)

## Building process:

This project uses cmake, python and conan for configuration and building automation, so the process itself is pretty easy, you don't need to configure or compile anything manually. You can find all necessary scripts in `configuration_scripts` directory of the project. I did some building tests on VMs, and they were succeeded, but if you have any problems, don't be shy to open an issue.

---

### Windows (mingw or visual studio)

1. Install [cmake][downloads-cmake] and [python3][downloads-python3] (and add them to path)

2. Install [conan][downloads-cpp-conan] via python pip: `pip install conan`

3. Install mingw64, you need exactly **[posix][posix-mingw64-builds]** version of the compiler, because win32 doesn't support some of thread functions (for example win32 mingw will fail on `std::this_thread::sleep_for`).

   *Or* you can just install visual studio with its c++ compilers and packages.

4. Make sure you have mingw64 bin directory (usually `C:\MinGW\bin`) in your `PATH` variable, and your `PATH` doesn't contain another version of MinGW compiler (like and especially win32), so cmake and conan can locate the compiler correctly. And also check your cmake and python binaries are in the `PATH` variable too, otherwise scripts won't work.

5. Run one of python scripts in

   `configuration_scripts/gcc_universal` or

   `configuration_scripts/visual_studio` depending of the choice of compiler.

   You have the following options here:

   - `configure_<mode>.py` - conan libraries installation and cmake configuration for debug or release

   - `build_<mode>.py` - same as above, but also run `cmake --build` command for building.

---

### Linux (gcc)

1. Install [cmake][downloads-cmake], [python3][downloads-python3], [conan][downloads-cpp-conan] and gcc compiler:

   `sudo apt install cmake python3 gcc`

   `pip install conan`

2. Run one of python scripts in

   `configuration_scripts/gcc_universal` or

   `configuration_scripts/visual_studio` depending of the choice of compiler.

   You have the following options here:

   - `configure_<mode>.py` - conan libraries installation and cmake configuration for debug or release

   - `build_<mode>.py` - same as above, but also run `cmake --build` command for building.



[posix-mingw64-builds]: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/

[downloads-cmake]: https://cmake.org/

[downloads-python3]: https://www.python.org/

[downloads-cpp-conan]: https://conan.io/
