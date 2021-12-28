# Building ChessClock

## Windows
TODO

## Ubuntu/Raspian


### Pre-requisites


```bash
sudo apt-get update 
sudo apt-get install build-essential git-lfs libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev uuid-dev
sudo apt-get install libboost-chrono.dev libboost-filesystem.dev libboost-program-options.dev libboost-system.dev libboost-date-time-dev 


git clone https://github.com/cschladetsch/ChessClock.git
cd ChessClock
git lfs init
git fetch origin develop
git checkout develop
git submodule init
git submodule update --recursive

```

# Building
Type `./run` (or .\run on Windows)

