# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi* and a relatively large screen.

There are many floating ideas about [Features](Features.md) that may never see the light of day.

This image is is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Ingredients
* Raspberry Pi 3 [Model B+](https://raspberry.piaustralia.com.au/products/raspberry-pi-3-model-b-plus)
* [7" Display](https://raspberry.piaustralia.com.au/collections/displays/products/little-bird-5-display) Or Smaller. See [Display](display).
* 3d Printed body with custom rocker switch.
* [Speaker](https://raspberry.piaustralia.com.au/products/speaker-kit-for-raspberry-pi)
* Unity3d. See [Architecture](Architecture.md) for details on code structure and implementation.
* Art
* [Battery](https://www.18650batterystore.com/collections/18650-batteries)

### Later

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

