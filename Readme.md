# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi*, and a relatively large screen.

There are many ideas about [Features](../../wiki/Features) that may never see the light of day.

This image is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Building

TODO: Add separate [Building](Building.md) instructions.

### Raspberry Pi Setup
```bash
$ sudo apt update
$ sudo apt install git-lfs
$ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf2.0-dev libsdl2-mixer-dev
```

### Building

Simply, `./run` will build and run the app on either Windows10 or Raspberry Pi. Or anything else I think. 

For more details:

```bash
$ git clone https://github.com/cschladetsch/ChessClock.git
$ cd ChessClock
$ git submodule init
$ git submodule update --recursive
$ mkdir build && cd build && cmake ..
```

Now, for Windows either open and build ChessClock.sln or run `msbuild ChessClock.sln`

Otherwise simply run `make`.

The output will be in `../bin` folder in either case. There is a `run` script in that folder.

For windows, set Debug command arguments to `..\..\ChessClock\Resources\ main.json` to run from Visual Studio.

## Ingredients
* [Hardware](../../wiki/Hardware)
* 3d Printed body with custom rocker switch
* [Software](../../wiki/Software)
  * The app is based on a purpose-built but general system, [Gambit](Gambit).
  * The main source tree is in [ChessClock](ChessClock).
* Art

## Wiki

There is a developing [Wiki](../../wiki/Home) in progress.

## Jira

There's a [Jira board](https://chessclock.atlassian.net/secure/RapidBoard.jspa?rapidView=1&selectedIssue=CHES-3) to keep track of things.

## Chess Clock Body

The body is self-contained and runs off a LiPo battery. A means to readily pull apart the shell, to turn the device on and off, and to change the battery are all required.

### Rocker

This is a key component of the project. If this doesn't feel/work well, the project fails.

#### Switches

Want micro-switch at the end of travel. Based on magnets.

## Connecting ADB
It's better to use [VNC](https://www.realvnc.com/en/connect/download/viewer/).

But there are other ways to interact with the Pi:
```bash
$ adb connect ip-address:5555 # find the ip-address on Pi/About settings
```

Or using `ssh`
```bash
# ssh pi@your.pi.address:5555
```
## Art

Various art assets will be required, such as:

* Fonts
* Backgrounds
* Animations
* Transitions
* Sound Effects

## Future Work

* Android Connectivity via Bluetooth
* [Lichess API](https://lichess.org/api)

