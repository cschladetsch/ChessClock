# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi*, and a relatively large screen.

There are many ideas about [Features](../../wiki/Features) that may never see the light of day.

This image is is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Ingredients
* [Hardware](../../wiki/Hardware)
* 3d Printed body with custom rocker switch
* [Software](Software)
* Art

## Hardware/Software setup 
TODO

### SDL 2.0

Latest and last attempt to get a system up and running that can be dev'd on Win10 and built on device.

#### Build SDL for Windows

Prerequisites:
* [VncViewer](https://www.realvnc.com/en/connect/download/viewer/)
* [GitBash](https://github.com/git-for-windows/git/releases/download/v2.31.1.windows.1/Git-2.31.1-64-bit.exe)
* [Doxygen](https://doxygen.nl/files/doxygen-1.9.1-setup.exe).
* [Cmake](https://cmake.org/download/)
* [Make](https://ixpeering.dl.sourceforge.net/project/ezwinports/make-4.3-without-guile-w32-bin.zip)

```bash
$ git submodule update --init --recursive

$ mkdir build && cd build && cmake .. && start main.sln
```
Now, build the library using Ctrl-Shift-B and close visual studio.

## Future Work

* Android Connectivity via Bluetooth
* [Lichess API](https://lichess.org/api)

## Wiki

There is a developing [Wiki](../../wiki/Home) in progress.

## Jira

There's a [Jira board](https://chessclock.atlassian.net/secure/RapidBoard.jspa?rapidView=1&selectedIssue=CHES-3) to keep track of things. TODO: Update Jira with `Epics`.

## Chess Clock Body

The body is self-contained and runs off a LiPo battery. A means to readily pull apart the shell, to turn the device on and off, and to change the battery are all required.

### Rocker

This is a key component of the project. If this doesn't feel/work well, the project fails.

#### Switches

Want micro-switch at the end of travel:

![RockerSwitch](External/RockerSwitch.png)

## Connecting ADB

```bash
$ adb connect ip-address:5555 # find the ip-address on Pi/About settings
```

## Art

Various art assets will be required, such as:

* Fonts
* Backgrounds
* Animations
* Transitions
* Sound Effects

