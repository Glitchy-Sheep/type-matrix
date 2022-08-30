## About 🐇

This app is highly inspired by [cmatrix][cmatrix-repo] project.
It turns your command line into a matrix-like terminal ([preview](#preview)).
However, it has some unique features such as an interactive mode, changing the alphabet, and changing the line length.
In interactive mode, symbols fall only when you're typing text with your keyboard.
It also maps keys' position to symbols' position, so if you type from the left, symbols fall from the left.<br>
<br>
All you need is just run it and follow the white rabbit.

## Table of contents:

1. [Usage](#usage)
2. [Preview](#preview)
3. [How to build](#how-to-build)

## Usage

Type-matrix has a few options, you can find them if you pass `--help` option.<br>
If you run it without any options they will be the default.

```
Available options:
-h --help             show this help message

-i --interactive      matrix falls only when you're typing.
                      so you can impress your friends with your hacker skills B)

-c --color            set matrix main color  (default=green)
  Available colors:
  black, blue, cyan, green, magenta, red, white, yellow

-r --rainbow          turn on matrix disco mode. (ignores --color)

-b --bold             enable random bold symbol generation  (default=disabled)

-f --fps              set matrix frames per second limit  (default=15)

-l --length           set maximum length of a line tail  (default=8)

-d --deviation        set minimum length of a line via deviation (default=3)
                      this option calculates minimum length as a difference between
                      length  value and deviation value, so for example:
                      [length=8 deviation=3 -> min_length = 8-3 = 5]

-a --alphabet         set matrix alphabet as a single string
                      example: -alph abc123

-s --screensaver      exit the program if any key is pressed

-m --message          print some message to the center of the screen

-C --message-color    set message main color
  Available colors:
  black, blue, cyan, green, magenta, red, white, yellow
```

## Preview

<p align="center">
  <b>Normal mode:</b> <br><br>
  <img width="600" src="https://github.com/Glitchy-Sheep/type-matrix/raw/assets/preview_normal_mode.gif"> <br><br>
  <b>Interactive mode (I'm typing here):</b> <br><br>
  <img width="600" src="https://github.com/Glitchy-Sheep/type-matrix/raw/assets/preview_interactive_mode.gif"><br><br>
</p>

## How to build
This project uses [conan package manager](https://conan.io/)
and [CMake](https://cmake.org/) for building automation, so you need to install them first.<br>
_If you don't like package managers, you also can link all the libraries manually._

### Dependencies
  1. [Argh!](https://github.com/adishavit/argh)
  2. [pdcurses](https://pdcurses.org/) (for windows) /
     [ncurses](https://invisible-island.net/ncurses/) (for linux)

### Building process (Windows)
  1. Install [python3](https://www.python.org/) and conan (`pip install conan`).
  2. Install [CMake](https://cmake.org/).
  3. Make sure you have some compiler in your system, so CMake can recognize it as a generator.
  4. Open command line in the project root directory.
  5. Run conan configuration script (`configure_debug.bat` or `configure_release.bat`)<br>
     It downloads all the required libraries, generates a `conanbuildinfo.cmake` file for CMake,
     creates build directory and generates all project files.<br>
  6. Run `cmake --build .` in the created `./build` directory.
  7. Your binaries are placed in `./build/bin`.

[cmatrix-repo]: https://github.com/abishekvashok/cmatrix
