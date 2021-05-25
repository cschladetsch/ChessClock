# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi*, and a relatively large screen.

There are many ideas about [Features](../../wiki/Features) that may never see the light of day.

This image is is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Ingredients
* [Hardware](../../wiki/Hardware)
* 3d Printed body with custom rocker switch.
* Unity3d 2020.3.0f1. TODO: Place link. See [Architecture](../../wiki/Architecture) for details on code structure and implementation.
* Art

## Hardware/Software setup 

### Native

```bash
$ sudo apt-get install libglm-dev
$ git clone Urho
$ # make Urho

```

### Android
To Install LineageOs 17.1:
1. Install Etcher
1. Flash drive with lineage-17.1-20201108-UNOFFICIAL-KonstaKANG-rpi3
1. Boot pi with card
1. Install F-Droid via built-in Browser
1. Install Termux
1. Alt-Shift-+/- to change font size of Terminal

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

