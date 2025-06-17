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
- `microex.y` - yacc grammar and semantic rules for parsing Micro/EX
- `microex.l` - lexical analyzer for tokenizing Micro/EX source code
- `microex.h` - contains symbol table definitions and expression attributes
- `teacher_test_case.txt` - test case provided by the instructor
- `lexical_error_case.txt` - triggers a lexical error by using invalid identifiers (e.g., @@@) (bonus)
- `undeclare_var_case.txt` - produces an error when referencing an undeclared variable (bonus)
- `undeclare_array_case.txt` - produces an error when accessing an undeclared array (bonus)
- `data_type_mismatch_case.txt` - reports a type mismatch error when performing operations between integer and float (bonus)
- `while_loop_case.txt` - basic while loop support (bonus)

## 📦 Output
| Input (teacher_test_case.txt) | Output |
|-------------|-----------------|
| ![Input](image/1.PNG) | ![Enhanced](image/2.PNG) |

| Input (while_loop_case.txt) | Output |
|-------------|-----------------|
| ![Input](image/3.PNG) | ![Enhanced](image/4.PNG) |

## 🚀 Getting Started
To compile the program:
```
yacc -d microex.y
lex microex.l
gcc lex.yy.c y.tab.c -ly -lfl
```
These commands will generate the following files:
- `y.tab.c`
- `y.tab.h`
- `lex.yy.c`
- `a.exe` or `a.out`

To run the compiler on different test cases:
```
./a < teacher_test_case.txt
./a < lexical_error_case.txt
./a < undeclare_var_case.txt
./a < undeclare_array_case.txt
./a < data_type_mismatch_case.txt
./a < while_loop_case.txt
```
