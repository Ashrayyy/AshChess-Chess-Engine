# AshChess Chess Engine

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Description

This is a relatively simple chess engine implemented in [C++]. It allows you to play chess against the engine, analyze games, and integrate it into other applications.

## Features

- Play against the engine
- Set timely moves, I.e., enter a time 'x' seconds, and the best move that could be made in x seconds would be made by the code
- Game analysis
- Simple function calls, that can be implemented in APIs.
- Multi-Threading Enabled

## Installation

Step 1: Clone this Repository
```
git clone https://github.com/Ashrayyy/AshChess-Chess-Engine.git
```
That's it, then compile the project.

### Note: The w64 MinGW Compiler will not be able to compile the project, you need to add future and threading libraries manually (or install a posix build of MinGW with multithreading support)

## Usage

### Run the Program
You can set time per move, or set the position in the code.

An infinite loops run that always waits for inputs
enter 0 for the engine to make the move
enter 1 for making a manual move.
enter 2 for skipping a turn (for development and debugging purposes (and for special moves like castling/promotion/en-passant))

## Contact

In case you want to contribute to the project, or if you have any queries, you can reach me at [ashrayy.tiwari@gmail.com] or dm me at my LinkedIn[https://www.linkedin.com/in/ashrayy/] !

