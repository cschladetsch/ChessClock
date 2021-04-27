# Software Architecture

## Clock-Base App
App that runs on custom device. Key problem found: Pi runs on Arm32 (duh), which limits a lot what can be done on device.

Using Unity3d to create an executable is not possible, unless I turn the Pi into an [Android Device](https://developer.android.com/things/hardware/raspberrypi). Not really willing to do this immediately if there is a better way. I already use my Pi for a couple other things. Then again, Pi's are cheap, and I'll need to buy one for the clock anyway.

Options:

1. Write a custom C++ app using SDL and/or IMGUI. 
   1. This will also mean using raw Bluetooth API.
2. Write a web site that runs on the device.
3. Go Back to blasting the Pi with Android and targeting it as such in Unity3d.

All of these have pros and cons. Still thinking about it all. More research required.

## Clock-Android App

App that runs on Android phone, and communicates with the `Clock-Base` app via Bluetooth.

Or, it could just browse to the device using a shared hotspot WiFi Connection.

Still unclear, needs more thought and research. Bi-directional asynchronous communications is important, so TCP or WIFI still good targets.

Also, I don't know really well how to make websites on PC that can be deployed on Pi. Pi can't use latest .NET Core, so it makes things harder again. This is all very murky at the moment. 

## Packages

Shared source code and art resources between all apps.

