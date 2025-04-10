# Seedling

Seedling is an x86-x64 assembler designed specifically for the Illeshian Compiler that is apart of the Illesian Suite. 
Seedlings backend is currently being translated into nasm for output, so that it can achieve it goal of assembling, and 
since it output is nasm, that allows the ld linker to be able to link it into a proper binary executable. Its not the best
approach but I do have the desire, to make the backend output a proper binary output, with the intel opcode when I understand it
more fully. For the time being, it still allows me to write and use Seedling, as the backend for Illeshian. Since both Illeshian
and Seedling both use the new scoping system that I created, this allows Illeshain and Seedling, to have a one to one transition.

[Seedling Home](https://github.com/ravenleeblack/Seedling/wiki)

[How to Compile](https://github.com/ravenleeblack/Seedling/wiki/How-to-Compile)

[Command Line Flags](https://github.com/ravenleeblack/Seedling/wiki/Command-Line-Flags)

[Scope Structure](https://github.com/ravenleeblack/Seedling/wiki/Scope-Structure)

[Syntax Structure](https://github.com/ravenleeblack/Seedling/wiki/Syntax-Structure)

[Programming in Seedling](https://github.com/ravenleeblack/Seedling/wiki/Programming-in-Seedling)

## CURRENTLY IMPLEMENTED:
- move instructions 
- compare instructions
- push and pop instructions
- increment and decrement instructions
- jump instructions to labels
- call instruction to labels
- pass_arg instruction to return
- call to yield label to exit
- write to console
- read to console
- system call instruction. So it can probably do alot more then I realize.

Currently working on opening, reading, and writing files. 
Still implementing and trying to figure out what all needs to be implemented. 

## TODO LIST:
- create a backend for Seedling that outputs binary.


