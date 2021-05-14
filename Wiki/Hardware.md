# 800x480Hardware Options

There will be various other bits and pieces, like LEDs for the rocker arms, connectors, and so on. I have most of that, or can get it from *JayCar* or something.

However, there are some larger decisions to be made. This documents attempts to list most obvious available options, their cost, and availability.

All Prices in AUD except where noted.

## Compute/IO

It won't be enough to have just a Pi. We will need digital and analog inputs as well. How exactly the Pi <=> Arduino connection will work needs a spec.

| What | Cost | Use | Avail |
|------|------|-----|-------|
| [Pi 3](https://www.littlebird.com.au/products/raspberry-pi-3-model-b-f1990217-84ed-4cd4-a75a-bd1962465bd8) | $69 | Main driver | No |
| [Arduino Uno R3](https://www.littlebird.com.au/products/uno-r3-little-bird) | $25 | Input Controller | Yes |

## Switches

These are used at the end-stops for the rocker arms. There's really only one option here because it's the best option. However will required printed parts for integration to rocker arm mechanism.

| What | Cost | Use | Avail |
|------|------|-----|-------|
| [Cherry Red Switch](https://www.littlebird.com.au/products/cherry-mx-switch-red) | $3.50 | Rocker Arm Switch | Yes|

## Speakers

Optional for prototype, but a nice to have. Could count-down time remaining, give voice feedback on state changes when setting up, etc.

| What | Cost | Use | Avail |
|------|------|-----|-------|
| [Stereo Speakers](https://www.littlebird.com.au/products/adafruit-i2s-3w-stereo-speaker-bonnet-for-raspberry-pi-mini-kit) | $50? | Sound output | Yes |

## Displays

This is a key to the entire system. TODO: Complete this table with details. The links are all different, I just haven't fill out the table yet.

| What | Touch? | Cost | Size | Res | Pi Ver? | Notes | Avail |
|------|------|------|-----|---------|-------|-------|-------|
| [PiTFT Plus](https://raspberry.piaustralia.com.au/products/pitft-plus-480x320-3-5-tft-touchscreen-for-raspberry-pi) | No | $126 | 3.5" | 480x320 | ? | | |
| [HDMI 5 Display Backpack](https://raspberry.piaustralia.com.au/products/hdmi-5-display-backpack-without-touch) | No | $169.88 | 5" | 800x480 | Everything | | Yes|
| [Little Bird 5” Display](https://raspberry.piaustralia.com.au/collections/displays/products/little-bird-5-display ) | Yes | $59 | 5" | 800x480 | 3B(+) | 5V, Has Pen | Yes|
| [Touch Screen Display](https://www.littlebird.com.au/products/5-inch-lcd-hdmi-touch-screen-display-for-raspberry-pi-3) | Yes | $59 | 5" | 800x480 | 3 | 5V, Has Pen |  Yes|
| [Touchscreen](https://www.littlebird.com.au/products/5-inch-lcd-hdmi-touch-screen-display-for-raspberry-pi-4) | Yes | $59 | 5" | 800x480 | 4 | 5V from Pi | Yes|
| [Touchscreen](https://raspberry.piaustralia.com.au/products/7-inch-lcd-hdmi-touch-screen-display-tft-for-raspb#description) | Yes | $106 | 7" | 800x480 | 3 | | Yes|

## Battery(s)

Battery is important as it has to provide the correct voltage ranges for the various components. A DC step-down circuit may be required. Preferably everything can run on 6-9V.

| What | Cost | Size | Voltage | Avail | Rechargeable |
|------|------|------|---------|-------|--------------|
| [Battery](https://www.18650batterystore.com/collections/18650-batteries) | ? | >AA | ? | Yes | Yes |
| 9Volt Battery | $9 | Medium | 9V | Yes | No |
| AA x 3 or 4 | $2 | AA | 1.5V | Yes | Optional |
| Something from RC World | ? | ? | ? | ? | Yes |
|  |  |  |  |  |  |

