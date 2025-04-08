# Seedling

Seedling is an x86-x64 assembler designed specifically for the Illeshian Compiler, part of the Illesian Suite. Unlike traditional assemblers that are section-based, Seedling adopts a unique scope-based approach to assembly programming.

## Overview

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

For more information check out the wiki!!

[Seedling Home](https://github.com/ravenleeblack/Seedling/wiki)


