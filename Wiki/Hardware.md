# Hardware Options

There will be various other bits and pieces, like LEDs for the rocker arms, connectors, and so on. I have most of that, or can get it from *JayCar* or something.

However, there are some larger decisions to be made. This documents attempts to list most obvious available options, their cost, and availability.

## Compute/IO

It won't be enough to have just a Pi. We will need digital and analog inputs as well. How exactly the Pi <> Arduino connection will work needs a spec.

| What | Cost | Use | Avail |
|------|------|-----|-------|
| [Pi 3](https://www.littlebird.com.au/products/raspberry-pi-3-model-b-f1990217-84ed-4cd4-a75a-bd1962465bd8) | $69 AUD | Main driver | No |
| [Arduino Uno R3](https://www.littlebird.com.au/products/uno-r3-little-bird) | $25 AUD | Input Controller | Yes |

## Switches

These are used at the end-stops for the rocker arms.

| What | Cost | Use | Avail |
|------|------|-----|-------|
| [Cherry Red Switch](https://www.littlebird.com.au/products/cherry-mx-switch-red) | $3.50 AUD | Rocker Arm Switch | Yes|

## Speakers

Optional for prototype, but a nice to have. Could count-down time remaining, give voice feedback on state changes when setting up, etc.

| What | Cost | Use | Avail |
|------|------|-----|-------|
| [Stereo Speakers](https://www.littlebird.com.au/products/adafruit-i2s-3w-stereo-speaker-bonnet-for-raspberry-pi-mini-kit) | $50? | Sound output | Yes |

## Displays

This is a key to the entire system. TODO: Complete this table with details. The links are all different, I just haven't fill out the table yet.

| What | Cost | Size | Res | Pi Ver? | Avail |
|------|------|------|-----|---------|-------|
| [Touchscreen](https://raspberry.piaustralia.com.au/products/pitft-plus-480x320-3-5-tft-touchscreen-for-raspberry-pi) | ? | 3.5" | 480x320 | ? | Yes|
| [Touchscreen](https://raspberry.piaustralia.com.au/products/hdmi-5-display-backpack-without-touch ) | ? | 5" | ? | 3 | Yes|
| [Touchscreen](https://raspberry.piaustralia.com.au/collections/displays/products/little-bird-5-display ) | ? | 5" | ? | 3 |  Yes|
| [Touchscreen](https://www.littlebird.com.au/products/5-inch-lcd-hdmi-touch-screen-display-for-raspberry-pi-3) | ? | 5" | ? | 3 |  Yes|
| [Touchscreen](https://www.littlebird.com.au/products/5-inch-lcd-hdmi-touch-screen-display-for-raspberry-pi-4) | ? | 5" | ? | 4 |  Yes|
| [Touchscreen](https://raspberry.piaustralia.com.au/products/7-inch-lcd-hdmi-touch-screen-display-tft-for-raspb#description) | ? | 7" | ? | 4 |  Yes|

## Battery(s)

Battery is important as it has to provide the correct voltage ranges for the various components. A DC step-down circuit may be required. Preferably everything can run on 6-9V.

| What | Cost | Size | Voltage | Avail | Rechargeable |
|------|------|------|---------|-------|--------------|
| [Battery](https://www.18650batterystore.com/collections/18650-batteries) | ? | >AA | ? | Yes | Yes |
| 9Volt Battery | $9 | Medium | 9V | Yes | No |

