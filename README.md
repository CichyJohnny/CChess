# CChess

CChess is simple desktop application made with C and SFML.

![demo](https://github.com/CichyJohnny/CChess/assets/137332118/537f2816-8ef7-4c4e-a1d2-2a94e3bc4c95)

## Software

- GCC 13.2.0
- CSFML 2.5.1
- VSCode 1.88.1

## Installation

1. Use the official SFML binding for the C language from [SFML project website](https://www.sfml-dev.org/download/csfml/).

2. Move files from SFML/bin/ to project directory.

3. (If VSCode) link SFML/bin, /include, /lib and your compiler inside files: [tasks](.vscode/tasks.json), [launch](.vscode/launch.json), [c_cpp_properties](.vscode/c_cpp_properties.json)

## Features

- Complete chess experience
- Implemented every chess rule
- Graphic representation of chessboard, chess pieces and game informations
- Saves
- Icon

Aditionally:
- Source and header files segmentation
- Full comprehensive documentation
- Error free

## Usage

- In VSCode compile with Run and Debug menu
- Launch game with CChess.exe
- Select figure with left-click, then click highlighted square
- Save or load using down right corner buttons
- Quit with close bar button, or ESC

## Libraries content

1. [actions](lib/actions.h)
   - Actions on pieces like normal move, en passant or pawn promotion
2. [chess_events](lib/chess_events.h)
   - Handling check, check mate and stale mate
3. [chessboard](lib/chessboard.h)
   - Initialization and drawing empty chessboard
4. [clashing](lib/clashing.h)
   - Handling king - rook clashing
5. [include_define](lib/include_define.h)
   - Include SFML library
   - Define game and figure structure
6. [moveboard](lib/moveboard.h)
   - Check and draw every legal move
7. [moves](lib/moves.h)
   - Chess pieces moves
8. [save_load](lib/save_load.h)
   - Save current game state to file
   - Load game from file
9. [sprites](lib/sprites.h)
   - Handling sprites of chess figures, save/load buttons and background
10. [texts](lib/texts.h)
    - Initalization of game informations texts

## TODO

- [x] documentation and README page
- [x] icon
- [ ] add sounds effect
- [ ] improve RAM efficiency
- [ ] better interactivity
