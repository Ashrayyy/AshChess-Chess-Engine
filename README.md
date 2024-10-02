<div align="center">
  <img src="https://github.com/Ashrayyy/AshChess-Chess-Engine/assets/101005702/bd918025-a04a-4ee1-850c-dfdcdb368c6d"/>

  <h1>AshChess Chess Engine</h3>

  A fun Chess Engine Written in C++.
  <br>
  <br>

</div>

[![License](https://img.shields.io/badge/license-GPLv3-green.svg)](https://opensource.org/license/gpl-3-0)

Note: This is a basic code that demonstrates the version of the engine, when their was need of constant debugging, the other version, being used as API is private as of now until fully developed.

## Description

This is a relatively simple chess engine implemented in [C++]. It allows you to play chess against the engine, analyze games, and play the best move in puzzles (custom positions).

## Features

- Play against the engine
- Set timely moves, I.e., enter a time 'x' seconds, and the best move that could be made in x seconds would be made by the Engine
- Game analysis
- Simple function calls, that can be implemented in APIs.
- Uses Multi-Threading Features in C++.

## Installation

Step 1: Clone this Repository

```
git clone https://github.com/Ashrayyy/AshChess-Chess-Engine.git
```

That's it, compile the project.

##### Note: The w64 MinGW Compiler will not be able to compile the project, you need to add future and threading libraries manually (or install a posix build of MinGW with multithreading support)

## Usage

### Run the Program
You can set time per move, or set the position in the code.

An infinite loops run that always waits for inputs
enter 0 for the engine to make the move
enter 1 for making a manual move.
enter 2 for skipping a turn (for development and debugging purposes (and for special moves like en-passant))

## Credits

This Chess engine was a fun project, I love chess and I wanted to make some project related to the game. 

The input move format is [Universal Chess Interface (UCI)](https://en.wikipedia.org/wiki/Universal_Chess_Interface)

The Opening file contains openings picked from [Chess-poster's Website](https://www.chess-poster.com/english/openings/chess_openings.htm) and also from Tom Kerrigan's SCP. 
Kudos to [LiChess](https://lichess.org/) for the great Master Database to pick and add selective Openings!

## References

This Engine DOES NOT USE BITMAPS to represent the chessboard. It uses a 2d vector to display the ChessBoard and evaluated positions on the basis of basic and advanced heuristics. These refereces sure got me a better understanding to complete the project.

- [ChessProgrammingWiki](https://www.chessprogramming.org/Main_Page)
- [TSCP (Tom Kerrigan's Simple Chess Program)](http://www.tckerrigan.com/Chess/TSCP/)

## Games



<p align="center">
  I am a 1700+ on Chess com and this was one of the few games I won, after sacrificing a Rook, a Bishop and then a Knight. This game was played at an early stage while developing the bot, when it didn't even had complex moves like castling and pawn promotions introduced.
  <br>
  <img width="460" height="300" src="https://github.com/Ashrayyy/AshChess-Chess-Engine/assets/101005702/c1e5dbac-4282-4b96-b5d0-71ba3f48292c">
  <br>
</p>

## How it works

#### Openings
When a game starts, the openings get loaded in a Trie Data Structure, I have also added the first 6 best moves from the Lichess Master Database into the openings. It randomly chooses the available options as per the previous moves.

##### What if I want to add my own openings to the opening Trie
It is simple, either just place UCI notations in the openings.txt file. Or if you have PGN, paste it into openingsGeneralNotations.txt and the run the pgn_to_uci.py script to get UCI notations in openingsUCInotation.txt, then you can copy and paste the UCI notations of openings into openings.txt!

As the game proceeds, the opening Trie gets searched on, once the nextTrie vector is empty (on reaching a terminal node), the engine does start calculating.

##### Calculating, how?

The Engine utilizes recursion techniques and advanced versions of the MiniMax algorithm and several Pruning techniques including Alpha-Beta Pruning to reduce the branching factor and prune not-so-good branches. and evaluates terminal nodes.

##### Evaluation, how?

The engine evaluates chess board position on the basis of heuristics (since computers can not get intutions as humans do).

I have tried to add comments at specific points to make the code more understandable, however for any doubts, you can reach out to me!

## Contact

In case you want to contribute to the project, or if you have any queries, you can [Email me](mailto:ashrayy.tiwari@gmail.com) or dm me at my [LinkedIn](https://www.linkedin.com/in/ashrayy/) !

