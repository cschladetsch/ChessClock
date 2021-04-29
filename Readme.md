# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

*ChessClock* is a somewhat ambitious project to make an elaborate Chess clock base on *Raspberry Pi* and a relatively large screen.

There are many floating ideas about [Features](Features.md) that may never see the light of day.

This image is is a conceptual render of the final product. It only shows relative sizes of each major component (body, screen, rocker), but you get the idea:

![ChessClock](External/SampleRender-1.png)

## Ingredients

* Raspberry Pi 3 [Model B+](https://raspberry.piaustralia.com.au/products/raspberry-pi-3-model-b-plus)
* [7" Display](https://raspberry.piaustralia.com.au/collections/displays/products/little-bird-5-display)
* 3d Printed Body
* [Speaker](https://raspberry.piaustralia.com.au/products/speaker-kit-for-raspberry-pi)
* Unity3d
* Ubuntu
* Android 10+
* [Lichess API](https://lichess.org/api)
* C#/C++ Code. See [Architecture](Architecture.md) for details on code structure and implementation.
* Art
* [Battery](https://www.18650batterystore.com/collections/18650-batteries)

## Body

The body is self-contained and runs off a LiPo battery. A means to readily pull apart the shell, to turn the device on and off, and to change the battery are all required.

### Rocker

#### Switches

## Code

See [Architecture](Architecture.md) for details.

## Art

Various art assets will be required, such as:

* Fonts
* Backgrounds
* Animations
* Transitions
* Sound Effects

