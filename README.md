# deliveries-simulation

Team project for the OOP course at Warsaw University of Technology

Authors:
* Dawid Kaszyński
* Mikołaj Szawerda
* Jan Kowalczewski

## Build
```
cmake -B ./build

cd ./build

make
```

## Run

```
./build/symulationApp path/to/map.txt
```

## Usage

Commands:

- addcourier [name] [localization] [capacity]
- addpackage [source] [destination] [size] [priority=1] [desc=""]
- statuscourier [id]
- statuspackage [id]
