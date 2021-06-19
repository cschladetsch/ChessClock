# Gambit ![Gambit](../External/gambit-icon.png)

*Gambit* is a general-purpose interactive system based on SDL2. It works on everything.

## Requirements

* CMake
* make, or msbuild
* C++11 compiler

### Windows 10

For building from Windows 10 to pi, nice to haves are:

* [VncViewer](https://www.realvnc.com/en/connect/download/viewer/) if working with external devices such as a Pi
* [GitBash](https://github.com/git-for-windows/git/releases/download/v2.31.1.windows.1/Git-2.31.1-64-bit.exe) Because the scripts are bash and you should use bash because everyone has since 1979.
* [Doxygen](https://doxygen.nl/files/doxygen-1.9.1-setup.exe) If you want some documentation.
* [Cmake](https://cmake.org/download/) To write the files that are used to make the system.
* [Make](https://ixpeering.dl.sourceforge.net/project/ezwinports/make-4.3-without-guile-w32-bin.zip) To make the binaries described by CMake. Can also use `msbuild` on Windows.

### Raspberry Pi

Either run `./run` or do it manually:

```bash
$ sudo apt update
$ sudo apt install make cmake git git-lfs
$ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
$ sudo apt upgrade
$ sudo apt autoremove
```

## Building

A script is provided:

```bash
$ ./run
```

In detail, see Raspberry Pi above and then:

```bash
$ git submodule update --init --recursive
$ mkdir -p build && cd build && build .. && make && cd ../bin && ./GambitTest
```

## Testing

```
$ ./boot tests
```

