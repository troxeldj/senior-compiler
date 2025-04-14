# Final Design Document

## Project Description

The goal of this senior design project was to build out a compiler from scratch for the C programming language to learn more about the world of compiler development. The compiler will be made up of the following components, a working: lexer, parser, and code generator. My objective is to make a compiler that is fairly easy to understand and provides the user with detailed error diagnostic information for easier use. The compiler should generate code in the x86 assembly language. I decided to use this language as x86 runs on almost any x86 and x64 machine and would provide the most compatibility among end-user devices. This project demonstrates the understanding of the components that make up modern compilers, their roles, and implementations of these components in a lower-level programming language (C). This project can later be extended with optimizations to further learn about that area as well.

## User Interface Specification

### Links
[Design Doc](https://github.com/troxeldj/senior-compiler/blob/master/design-document.md)

[User Guide](https://github.com/troxeldj/senior-compiler/blob/master/user-doc.md)


### Specification

This compiler doesn't come with a GUI interface; instead, we opt to use a Terminal interface that the user interacts with.

The first step is to compile and build the compiler, upon compilation, we will have an executable.

Prior to compilation, be sure to install these two packages using your package manager(via apt, yum, etc.)

note: these names are for the APT package manager on any Debian based Linux Distro
- gcc-multilib
- g++-multilib

These packages ensure that we have the needed binaries to compile the C code in x86

Next, we execute these commands to compile the project

```bash
git clone https://github.com/troxeldj/senior-compiler.git
cd senior-compiler
make
```

We then run this executable with

```bash
./main <C file name>
```

For example, for a C file named "main.c" in the current directory (root of the project), I would execute:

```bash
./main main.c
```

This would then compile this file using the compiler and output it to a file named "test.c" (by default, see the [user-doc](https://github.com/troxeldj/senior-compiler/blob/master/user-doc.md) for more configuration information)

Now that we have our executable we can run it via:

```bash
./test
```

If you're getting an error related to file permissions, try and run

```bash
chmod +x ./test
```

This will ensure you have execute permissions on the output file.

## Test Plan and Results

### Test Plan
Due to the complexity and size of this project (and it being done by a single member); testing was done on a per-feature basis. The feature would be present in the [test.c](https://github.com/troxeldj/senior-compiler/blob/master/test.c) file, be compiled, and then the output checked for errors.

This allowed me to integrate testing into the compiler as I was building the project. I found this to be more intuitive than testing it all at the end, as language features tend to build on top of one another.

### Implemented Features
Implemented Language Features:
- Characters (char)
- Integers (int, long, short, unsigned int, unsigned short, unsigned long)
- Floats
- Doubles
- Constants (const char, const int, const long, const short, const unsigned int, const unsigned short, const unsigned long, const float, const double)
- Strings (char * / const char*)
- Structures (structures containing primitives/other structures)
- Unions
- Preprocessor Directives (#include, #define, #ifndef, #ifdef, #endif)
- Functions (and return values)
- Pointer Types (int*, float*, double*, const double*, const float*, const int*, const long*, const short*, const unsigned int*, const unsigned short*, const unsigned long*, const float*, char*, const char*, struct*, union*)
- If/If Else/If Else If/If ElseIf Else Statements
- Switch Statements (with only integer values)
- Break, Continue Statements
- While Loops
- For Loops

### More Information

| Component | Additional Testing Information |
| --------- | ------------------------------ |
| Lexer | Each implemented language feature had to be tested to ensure that it generated the correct list of tokens based on what was put into the C file |
| Parser | Each implemented language feature had to tested to ensure that it generated a correct AST intermediate for the input C language code |
| Resolver | For each language feature, a test program was created, and the AST was analyzed to ensure it contained sufficent information to pass to the code generator for generation |
| Code Generator | For each language feature, the ouput assembly file was analyzed to ensure that it had the correct structure and information and was able to be linked and ran |

## User Manual

### Links

[Specification](#specification)

[User Documentation](https://github.com/troxeldj/senior-compiler/blob/master/user-doc.md)

[README](../README.md)

### FAQ

- Q: What is the goal of this project? Why make another C compiler?
	- A: The goal of this project was to learn about compiler development and explore the components that make up compilers. This compiler was created purely for educational purposes. I wanted to create a compiler from scratch without using any external dependencies.
- Q: What are the features of this compiler? What language features does this compiler implement?
	- A: This compiler compiles a subset of C into x86 assembly language. The subset can be found [here](#more-information).
- Q: Why choose C as the source language?
	- A: Being that I wanted to create a compiler that emitted assembly, this language was low-level enough that you have to think about sizing of the types. C's standard library is very versatile and allows a lot of low level os functions that make building compilation a bit easier. Also, there are an abundance of information ([Such as these](../README.md#sources)) that make it easier to build.
- Q: Does your compiler generate "Machine code"
	- A: This compiler does not output machine code. It produces x86 assembly, that is then linked using ld (from the C code executes a command) and assembled using NASM assembly (from the C code executes a command). This compiler replaces the job of something like gcc.
- Q: What is the architecture/structure of the compiler
	- A: The compiler follows standard procedure of Lexical Analysis ([lexer](../lexer.c)), Syntax Analysis ([parser](../parser.c) and [resolver](../resolver.c)), and code generation ([expressionable](../expressionable.c) and [generator](../codegen.c)).
- Q: What were the biggest challenges you faced building a compiler
	- A: Building a compiler is a large task. Each component has to be created so it's compatible with every other component, this was a big challenge. The biggest challenge however, was parsing, the building of the parser/resolver and enriching the AST with enough information (type sizes, types, struct member offsets, etc.) to make code generation easier.
- Q: What can be done to improve this compiler?
	- A: There are next to no optimizations make in the resulting assembly code. Optimizations can be made that results in neater, more efficient assembly code. This would cut down on the overall runtime. Also, implementing a standard library of functions that would allow the user to create/read/write to files, etc. would be a huge step.


## Final PPT Presentation

[Link](../Midnight_Compiler_Pres-troxeldj.pptx)

## Final Expo Poster

[PDF Link](../midnight_compiler_poster.pdf)

[JPG Link](../midnight_compiler_poster.jpg)

## Assessments

### Links

[Initial Assessment](../initial-self-assessment.pdf)

[Final Assessment](../self-assessment.md)

## Summary of Hours and Justification
### Task List and Hours
A typical compiler operates in stages, a compiler can have a multitude of different stages. However, for my project there will be four distinct stages:
1. Lexical Analysis (10 hours)
2. Parsing (20 hours)
3. Intermediate code Generation (6 hours)
4. Assembly (x86/x64) Code Generation (10 hours)
5. Testing/Debugging (7 hours)

Total: 53 hours

#### Lexical Analysis Tasks
1. Research Lexical Analysis and what the purpose of lexical analysis is within a compiler (2 hours)
2. Research implementations of Lexical Analysis Components (Lexers) in current language compilers; such as CPython (3 hours)
3. Develop the lexical analysis component (lexer) of the compiler (4 hours)
4. Test and QA the lexical analysis component(s) of the compiler (1 hour)

Total: 10 hours

Links:
- [compiler.h](../compiler.h)
- [lex_process.c](../lex_process.c)
- [token.c](../token.c)
- [lexer.c](../lexer.c)

#### Parsing Tasks
1. Research Parsing and what the purpose of parsing is within a compiler (4 hours)
2. Research the various types of parsing (recursive descent, top-down, bottom-up, etc.) to find the best fit for the project (4 hour)
3. Research Implementations of Parsing Components (Parsers) in current language compilers; such as CPython (2 hours)
4. Develop the parsing component of the compiler (9 hours)
5. Test and QA the parsing component(s) for the compiler (1 hours)

Total: 20 hours

Links:
- [compiler.h](../compiler.h)
- [node.c](../node.c)
- [scope.c](../scope.c)
- [stackframe.c](../stackframe.c)
- [parser.c](../parser.c)
- [resolver.c](../resolver.c)
- [symresolver.c](../symresolver.c)

#### Intermediate Code Generation & Code Generation Tasks
1. Research Intermediate code generation and common formats compilers use to generate intermediate forms (things such as three-address-code (TACS/3AC)). (2 hours)
2. Research intermediate code generation implementations in current language compilers; such as CPython (1 hours)
3. Develop the intermediate code generation component for the project's compiler (3 hours)
4. Research Assembly Code Generation implementations and how this process works in current compiler implementations; such as CPython (3 hours)
5. Develop the code generation component for the project's compiler (7 hours)

Total: 16 hours

Links:
- [expressionable.c](../expressionable.c)
- [codegen.c](../codegen.c)

#### Final QA Tasks
14. Test and debug the compiler as a whole. Ensure the interaction between components is functioning and the compiler generates correct assembly code. (7 hours)

Total: 7 hours


### Effort Matrix

| Milestone | Start Date | End Date |
| --------- | ---------- | -------- |
| Basic Lexer | 9/1/24 | Completed |
| Basic Parser | 9/1/24 | Completed |
| Basic Interpreter | 9/1/24 | Completed |
| Basic Generator | 10/7/24 | Completed |
| Function Support Added | 12/1/24 | Completed |
| Whole Project QA and Refactor | 2/1/24 | Completed |

## Summary of Expenses

Total Expenses: $0

There were no expenses made in the creation of this compiler. This is a pure software product.

## Appendix

### References

#### Dragon Compiler Course
- [dragon-compiler course](https://dragonzap.com/course/creating-a-c-compiler-from-scratch)
	- License: [GNU General Public License](https://github.com/nibblebits/DragonCompiler/blob/master/LICENSE)
		- No warranty/No Liability
- [dragon-compiler repo]()
	- License: [GNU General Public License](https://github.com/nibblebits/DragonCompiler/blob/master/LICENSE)
		- No warranty/No Liability
Credit to Daniel McCarthy and DragonZap Education. This is a very well put together course and is awesome for taking that next step in compiler development. This course helped tremendously and was used heavily in the creation of this compiler.

### Other references
- [Crafting Interpreters](https://craftinginterpreters.com/)
	- License: [Custom License](https://github.com/munificent/craftinginterpreters/blob/master/LICENSE)
		- No warranty/No Liability
	- [My implementation of JLox in C++](https://github.com/troxeldj/cppLoxv2)
- [Writing a Compiler in Go](https://compilerbook.com/)
	- License: [MIT License](https://github.com/kitasuke/monkey-go/blob/master/LICENSE)
		- No warranty/No Liability
- [C-Python](https://github.com/python/cpython/tree/main)
	- License: [Custom License](https://github.com/python/cpython/blob/main/LICENSE)
		- Software provided as is (No warranty/No Liability)
- [William Hawkins III](https://github.com/hawkinsw) for the help!