# Baghchal Game

Baghchal is a 2-player game between Tigers and Goats. This Readme provides an overview of the game and details about the code structure.

## Overview

Baghchal is played on a 5x5 board. There are 4 Tigers and 20 Goats. Tigers start from the corners of the board, and Goats are placed initially on the board. The game is played in turns, with Goats moving first followed by Tigers.

The objective of the Tigers is to eat Goats by jumping over them, while the Goats aim to restrict the Tigers' movement until they have no valid moves. Tigers win by eating 5 Goats, and Goats win by restricting all 4 Tigers.

## Code Structure

The code consists of classes representing Tigers and Goats, along with functions for game logic and user interaction. Here's a brief overview:

- `is_connected`: Function to check if two points on the board are connected.
- `Display`: Function to display the current state of the board.
- `initialize_board`: Function to initialize the game board.
- `menu_option`: Function to display the menu options and get user input for initial choice.
- `validate_coordinates`: Function to validate user input for coordinates of gaots and tigers.
- `first_20_moves`: Function to handle the first 20 moves of the game. During this part, the goats are not allowed to move, they can only be placed in the board while the tigers can move.
- `remaining_moves`: Function to handle moves after the initial 20 steps. During this part, the goats can move one step at a time. The aim of the goats is to move such that they restrict the tiger.
- `Goats` class: Represents a Goat, with methods for setting position, moving, and checking connections.
- `Tiger` class: Represents a Tiger, with methods for setting position, moving, and checking validity of moves.

## How to Play

Use VS code or Windows based compiler to ensure that the code runs properly. Some codes in the file like system ("clear") that doesn't work in xcode.

1. Run the code and select "Play Game" from the menu by choosing option 1.
2. Follow the on-screen instructions to place Goats on the board and make moves for both Goats and Tigers.
     That includes choosing the tiger and goats by entering the coordinates and entering the coordinates of the final position of the tigers or goats to move.
     For the first 20 steps, the goats can only be placed on the board and can't be moved while the tiger can be moved and can start eating
     After the first 20 steps, the goats can start moving in the board and no more goats can be placed on the board.
     The aim of the tigers is to eat 5 goats and the aim of the goats is to restrict the moves of all 4 tigers.
3. Continue playing until one player wins by achieving their objective.
4. In case the players are confused about the rules of the game, they can select the option 2 to access the help menu and learn the rules of the game.

Remember to enter coordinates in the format "row column" and follow the rules of the game.
Also there are no restrictions while entering the coordinates of the points until and unless valid coordinates are entered. (1,2) [1 2) 1,2 or 1 2 all mean the same coordinate.
Enjoy playing Baghchal!
