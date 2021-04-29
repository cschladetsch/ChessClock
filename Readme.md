# Chess Clock ![image](External/old-clock.png)

[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/chessclock/badge)](https://www.codefactor.io/repository/github/cschladetsch/chessclock)[![License](https://img.shields.io/github/license/cschladetsch/chessclock.svg?label=License&maxAge=86400)](./LICENSE.txt)[![Release](https://img.shields.io/github/release/cschladetsch/chessclock.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/chessclock/releases/latest)

![ChessClock](External/SampleRender-1.png)

## Ingredients

* Raspberry Pi 3 [Model B+](https://raspberry.piaustralia.com.au/products/raspberry-pi-3-model-b-plus)
* [7" Display](https://raspberry.piaustralia.com.au/collections/displays/products/little-bird-5-display)
* 3d Printed Body
* [Speaker](https://raspberry.piaustralia.com.au/products/speaker-kit-for-raspberry-pi)
* Unity3d
* Ubuntu
* [Lichess API](https://lichess.org/api)
* C#/C++ Code. See [Architecture](Architecture.md) for details on code structure and implementation.
* Art
* [Battery](https://www.18650batterystore.com/collections/18650-batteries)

## Body

The body is self-contained and runs off a 6550 LiPo battery. A means to readily pull apart the shell, to turn the device on and off, and to change the battery are all required.

### Rocker

#### Switches

## Code

This will be the hard part. The app will be developed on Windows 10 and deployed to Raspberry Pi which uses an Arm7 CPU.

Deciding even on the tech stack is difficult. There are so many options:
1. Native C++ app using Wifi or Sockets
2. WebApp using Node.js and React
3. Headless or not
4. How to develop on Win10 and deploy to Arm7 using Dotnet Core
5. What versions of everything to use
6. Actually developing the software

None of this has been resolved yet. I completely underestimated the compexity of the code requirements for this project.

## Art

Various art assets will be required, such as:

* Fonts
* Backgrounds
* Animations
* Transitions
* Sound Effects

