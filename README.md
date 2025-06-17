## 📝 Micro/EX Compiler Code Generation
A partial compiler for the Micro/EX language is implemented using Lex, Yacc, and C.

This project includes full support for lexical analysis, syntax parsing, and basic code generation.

However, only basic features are supported — nested or complex constructs are not yet implemented.

### 🔗 1132 NTNU CSIE Compiler Design Final Project

- Course code: 3N6463701
- Instructor: Prof. Gwan-Hwan Hwang(黃冠寰 教授)
- Textbook:
  - Crafting a Compiler with C, by Richard J. LeBlanc, Jr.
  - Lex & Yacc, by John R. Levine, Tony Mason, and Doug Brown, O’Reilly & Associates

📁 Contents
- `microex.y` - acc grammar and semantic rules for parsing Micro/EX
- `microex.l` - lexical analyzer for tokenizing Micro/EX source code
- `microex.h` - contains symbol table definitions and expression attributes

## 📦 Output
| Input | Output |
|-------------|-----------------|
| ![Input](image/input.png) | ![Enhanced](image/enhanced.png) |

| Input | Output |
|-------------|-----------------|
| ![Input](image/input.png) | ![Enhanced](image/enhanced.png) |

## 🚀 Getting Started
To compile the program:
```
yacc -d microex.y
lex microex.l
gcc lex.yy.c y.tab.c -ly -lfl
```
