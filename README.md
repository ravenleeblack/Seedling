# Seedling

Seedling is an x86-x64 assembler designed specifically for the Illeshian Compiler, part of the Illesian Suite. Unlike traditional assemblers that are section-based, Seedling adopts a unique scope-based approach to assembly programming.

## Overview

Seedling introduces a scope-based paradigm, differing from the conventional section-based structure of most assemblers. It was crafted to align seamlessly with the Illeshian Compiler, ensuring a one-to-one correspondence between scopes in the Illeshian language and the assembler. The supported scopes include:

- Universal Scope
- Global Scope
- Global Block Scope
- Local Scope
- Local Block Scope

Seedling is one component of the broader **Illesian Suite**, which comprises the following programs:
- **Illeshian Driver**
- **Illeshian Runtime Processor**
- **Illeshian Compiler**
- **Seedling (Assembler)**
- **Rootling**

The syntax and keywords in Seedling are derived from Illeshian to streamline the workflow between the compiler and assembler.

## Installation

I use vscode with the wsl2 terminal so that I can use both windows and linux.

To build Seedling from source:

```bash
make clean
make all

./seed -o -t -d -n main.seed yield.seed
```

flags:
```
-o: Output flag

-t: scope table flag - outputs the scope table variables or placeholders into a scope table that can
 be read in order to verify.

-d: debug flag**

-n: nasm flag - currently outputs nasm in the backend so that it can be assembled down and linked.

-b: binary flag - Will eventually have a way to assemble down in to binary so that we can lin with rootling
linker. If i ever make it that far. Rootling doesnt exist yet. I need to get an actual version od seedling
done first.
```
main.seed yield.seed: Input files for assembly. A seedling file must have the ext .seed

## Structure

Every label has a header, a body, and a footer. In the header we must declare the scope followed by the label name followed by
a colon.

```
universal _start:
```

Then under that we declare our sections.
```
    .code_sect 
        call main; 
    .end
```

I am still working out the footer. Right now since I dont do a line by line it a block structure so the footer is after the last bracket.
```
} pass_arg: num_value[0];
```
full:
```
universal start:
{
    .arch_32  
    .end
    .file_sect
        extern: yield;
    .end
    .code_sect 
        call main; 
    .end
} pass_arg: num_value[0];
```
This makes sure that the scope and the sections tied to that scope are sperated better. In illeshian everything outside a function is universal 
scope. Once you call a first class function that is a manager function then we have a global scope or a global label in seedling. THe manager can
two kinds of child functions. 

- A regular function
- A seedling function
  
These child functions are local scope.

Illeshian looks at everything that is not data or data types like its a data tool becuase they are tools that can change the data in some way so
things that would normally be classified as a statement are just data tools. When these tools are used in the manager body then these tools body 
become global block scope or it gets a global block scope label in seedling. When these tools are in a child function the body of the data tools
become a local block scope or gets a local block scope label in seedling.

## Currently

Right now in order to accomplish the scope based structure I have to create 3 temp files: temp_bss, temp_data, and temp_text.
Then I take all the sections from under every scope header then append them to the right temp file so that later we can append 
that to the nasm file in the right section order that nasm requires. It will be nice when we can output binary so that we remove
the temp files.

