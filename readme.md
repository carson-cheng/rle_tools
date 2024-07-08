# Usage

This library contains tools for processing RLEs and running them in Conway's Game of Life. All the functions are in the life.h file in this repository, including:

- Parsing and decompressing RLEs
- Getting the population and bounding box of Life patterns
- Copying and pasting patterns
- Running Life patterns

# 1-glider Seed Generation Program

Apart from the RLE tools, there is also a program that generates 1-glider seeds (basically, collisions of a glider with a constellation of still lifes). There are multiple input files for those (such as genp2seed.cpp and genseed_2.cpp, and also genseed_enum.cpp) which does an enumeration for a particular search space of glider + still life collisions, and also a genseed_tandem.cpp program that analyzes the output of the generator and prints out any collisions that result in the release of tandem gliders (any number of gliders going in the same direction) (xWSSes are also output).

To modify the list of still lifes for the searching:
- Input the list of the apgcodes of the still lifes in the gen_cats.py file (in line 5, the pats variable)
- Run gen_cats.py, and copy the line that is output into the console
- In the genseed configuration file, replace the cats_comp 2D array (should be right around line 12 or 13) with the line that is being copied from the console.
- Compile the updated program

To modify the number of still lifes used for the searching:
- See if there is a numSL variable (it should be present around line 19 in genp2seed.cpp, for example); if so, change its value to what you want, and then recompile
- Otherwise, look for a for-loop which contains something like "board = paste(board, cats[rng()%num], rng()%x+1, rng()%y+1);"; change the number of times that the for-loop runs

# Compilation

Remember to compile the scripts with 
-std=c++11 -O3

For example, g++ genseed.cpp -o genseed -std=c++11 -O3
