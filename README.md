# particle-universe-cpp

A particle simmulation built with C++ using SFMML, has merging of objects as well as explosions.

## Features

- Basic gravitational calculations
- Merging of particles, collisions combine particles
- Explosions, particles that grow above a certain size disappear and move all near particles
- Continuous generation of particles to always retain the same amount of particles

## Tech Stack
- C++23
- Clang++
- SFML 3

## Building

### Requirements
- C++ compiler supporting C++23
- CMake
- SFML 3

### Compilation
```bash
cmake -S . -B build
cmake --build build
```
