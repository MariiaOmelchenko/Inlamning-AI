# Inlamning-AI
# Kontaktbok med MySQL och TUI (Text User Interface)

## Beskrivning
Det här projektet är en kontaktbok skriven i C++ med ett Text User Interface (TUI). Projektet använder MySQL som databas för att lagra kontaktinformation.

## Funktioner
- Lägg till kontakter med namn, e-post och telefonnummer.
- Sök kontakter baserat på namn, telefonnummer eller e-post.
- Uppdatera och ta bort kontakter.
- Intuitivt TUI-baserat gränssnitt.

## Krav
- C++17 eller senare.
- MySQL-server installerad.
- CMake för att bygga projektet.

## Installation och användning
1. Klona detta repo.
2. Kör följande kommandon:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ./Kontaktbok

Installera beroenden med vcpkg:
./vcpkg install pdcurses mysql-connector-cpp

Bygg projektet:

mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
make

Starta programmet:

./Kontaktbok