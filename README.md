# Seedling

Seedling is a x86-x64 assembler that was designed for the Illeshian Compiler. Seedling is scope based instead of section based like normal assemblers.

To use:
```
make clean

make all

./seed -o -t -d -n main.seed yield.seed
```
I just seperated all the programs in the compilation process for what I am calling the Illesian Suite so there may be some things still a little off about 
some of the other programs. Right now this one will compile even doe their is a segmentation fault with the code provided. I haveto go back in now that I
have seperated everything and redo the syntax of the language to work better. I had changed it way too much beforehand.
