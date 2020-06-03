# Game of Life - C Programming Assignment - Year 2

### Overview
This assignment asked me to create an implementation of Conway's Game of Life using C. The requirements were to create a shared object library and to make a dynamically linked library.

## gameoflife.c
This file is the main executable for the Game of Life. It parses all inputs including flags or universes but relies on the functions in `gol.h` and `gol.c` to work properly. 

## Run
To compile the executable, run the command `make` in the terminal in this folder. Once it has compiled, run it using 
`./gameoflife` and with any flags. 

### Flags 
`-i [in file]` specify an input file containing a universe. Universes are text files made of `.` for a dead cell and `*` for an
alive cell. It should contain a blank line at the end of the file. If the flag is not supplied it will take a text 
input from the command line, which is terminated with `ctrl + D`. 

`-o [out file]` specify an output file. If the flag is not supplied it will print the output to the terminal. 

`-g [number of generations]` the number of generations to perform. If not supplied will do 5 generations by default. 

`-t` enable torus mode. Any edge cell will wrap around and take the cell on the opposite edge to be it's neighbour. 

`-s` print statistics. 

### universe files
Move any text file into the directory with the `gameoflife` executable to be able to use it. 