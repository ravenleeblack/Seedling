# Seedling

Seedling is an x86-x64 assembler designed specifically for the Illeshian Compiler that is apart of the Illesian Suite. 
The current state of the assembler is that its backend is being translated into nasm, in order for it to be able to assemble, and 
that allows ld to be able to link it. So it has a nasm backend with hope of a binary backend in the future.

[Seedling Home](https://github.com/ravenleeblack/Seedling/wiki)

[How to Compile](https://github.com/ravenleeblack/Seedling/wiki/How-to-Compile)

[Command Line Flags](https://github.com/ravenleeblack/Seedling/wiki/Command-Line-Flags)

[Scope Structure](https://github.com/ravenleeblack/Seedling/wiki/Scope-Structure)

[Syntax Structure](https://github.com/ravenleeblack/Seedling/wiki/Syntax-Structure)

[Programming in Seedling](https://github.com/ravenleeblack/Seedling/wiki/Programming-in-Seedling)

## CURRENTLY IMPLEMENTED:
- use move instructions 
- use compare instructions
- use push and pop instructions
- use increment and decrement instructions
- use jump instructions to labels
- use call instruction to labels
- use pass_arg to return and yield to exit
- write to console
- read to console
- uses system call instruction. So it can probably do alot more then I realize.

Currently working on opening, reading, and writing files. 
Still implementing and trying to figure out what all needs to be implemented. 

## TODO LIST:
- create a backend for Seedling that outputs binary.


