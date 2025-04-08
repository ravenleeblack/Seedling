# Seedling

Seedling is an x86-x64 assembler designed specifically for the Illeshian Compiler, part of the Illesian Suite. Unlike traditional assemblers that are section-based, Seedling adopts a unique scope-based approach to assembly programming.

For more information check out the wiki!!
[Seedling Assembler](https://github.com/ravenleeblack/Illeshian/blob/main/03_comp_source/README.md)

## Overview

Seedling introduces a scope-based structure. It was crafted to align seamlessly with the Illeshian Compiler, ensuring a one-to-one correspondence between scopes in the Illeshian language and the assembler. The supported scopes include:

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


