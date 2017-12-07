# Life
Conway's Game of Life. Can I program something interesting?

This was exclusively programmed during my last night shift at the PRIME lab. It was something fun to do and now it's done.
It has colors for tiles. Green is a newly live tile, white is a persistent live tile, red is a recently deceased tile.
Colors can be disabled by removing the definition for COLOR in the code.
The program automatically sizes to fill the terminal or two arguments can be given specifying the height and width in characters.
If only one argument is given, the program will use it as the seed for the pseudo random number generator. This can be used to create identical starting conditions.
Hard-coded into the program are two sets of coordinates. One set describes a single glider, while the other describes a glider gun.
