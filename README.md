# 15-Puzzle-Game

1/Board things:
	- Display the game
	- Move the block in the board (as user's command)
	- Check whether the user is win not not
	- Display an individual tile
	- Randomize the starting state
2/User things:
	- Get command from user
	- Able to click the tasks for some hints
	- Allow to quit (before/after) winning
	- Handle invalid input


			*****Class:*******
1/ Board
	- Display the game	- 2D array of Tile
	- Check whether the user is win not not
	- Move tiles
	- Randomize the starting state

2/ Tile
	- Display tile 	-int number

3/ namespace UserInput: 
	- Receive input
	- Handle invalid input

4/ Function main
	- Main game logic loop		
	- Allow to quit before winning

 			******Helpler Class*******
1/ Class Point
	- Implement as int x ,y pairs of index
	=> To help indexing the board tiles

2/ Class Direction
	- Implement as enum (can only receive expected input => Avoid invalid input)
	- Help to clarify the input command (Instead of 'a' -> Direction::left)