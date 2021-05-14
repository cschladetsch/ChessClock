# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi* and a relatively large screen.

There are many floating ideas about [Features](Features.md) that may never see the light of day.

This image is is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Ingredients
* [Hardware](Hardware)
* 3d Printed body with custom rocker switch.
* Unity3d 2020.3.0f1. See [Architecture](Architecture.md) for details on code structure and implementation.
* Art

## Future Work

* Android Connectivity via Bluetooth
* [Lichess API](https://lichess.org/api)

## Wiki

See the [wiki](Home) for details. TODO: will always need more documentation in the Wiki. More so, it has to be kept up to date with development.

## Jira

There's a [Jira board](https://chessclock.atlassian.net/secure/RapidBoard.jspa?rapidView=1&projectKey=CHES&config=columns&selectedIssue=CHES-3) to keep track of things. TODO: Update Jira with `Epics`.

## Chess Clock Body

The body is self-contained and runs off a LiPo battery. A means to readily pull apart the shell, to turn the device on and off, and to change the battery are all required.

### Rocker

This is a key component of the project. If this doesn't feel/work well, the project fails.

#### Switches

Want micro-switch at the end of travel:

![RockerSwitch](External/RockerSwitch.png)

## Code

See [Architecture](Architecture.md) for details.

Will support generation of Fischer Random locations.

### Connecting ADB

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

