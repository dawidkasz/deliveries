# 22L PROI Projekt Spedycja

Projekt grupowy z przedmiotu PROI w semestrze 22L  
Autorzy:
* Dawid Kaszyński
* Mikołaj Szawerda
* Jan Kowalczewski

## Opis działania
## Uruchomienie programu
Konfiguracja
```
cmake -B ./build
```
Budowa plików wykonywalnych
```
cd ./build
make
```
Uruchomienie aplikacji
```
./build/symulationApp path/to/map.txt
```

## Użytkowanie

Dostępne komendy:

- addcourier [nazwa] [lokalizacja] [pojemność]
- addpackage [skąd] [dokąd] [rozmiar] [priorytet=1] [opis=""]
- statuscourier [id]
- statuspackage [id]


