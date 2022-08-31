# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi*, and a relatively large screen. Done in collaboration with Conor O'Kane.

There are many ideas about [Features](../../wiki/Features) that may never see the light of day.

This image is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Building

See separate [instructions](Building.md).

The output will be in `../bin` folder. There is a `run` script in that folder.

For Visual Studio, set Debug command arguments to `--resources=..\..\ChessClock\Resources --main=main.json`.

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

There's a [Jira board](https://chessclock.atlassian.net/secure/RapidBoard.jspa) to keep track of things. Also, GitHub issues are a thing.

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


