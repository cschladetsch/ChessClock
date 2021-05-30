# Main Source Tree
This is the main source and include files for the project, as well as build files.

## Requirements
* CMake
* make
* C++11 compiler

### Windows 10

Prerequisites:

* [VncViewer](https://www.realvnc.com/en/connect/download/viewer/)
* [GitBash](https://github.com/git-for-windows/git/releases/download/v2.31.1.windows.1/Git-2.31.1-64-bit.exe)
* [Doxygen](https://doxygen.nl/files/doxygen-1.9.1-setup.exe).
* [Cmake](https://cmake.org/download/)
* [Make](https://ixpeering.dl.sourceforge.net/project/ezwinports/make-4.3-without-guile-w32-bin.zip)

### Raspberry Pi

TODO

## Building

In general:

```bash
$ git submodule update --init --recursive
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

## Running

You must supply the folder for resources.

```
$ build/main Resources/
```
