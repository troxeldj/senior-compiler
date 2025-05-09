# Senior Design Design Report

## Team Members
- Dillon Troxell
  troxeldj@mail.uc.edu

## Project Description
A compiler for a custom programming language. This programming language will support constructs such as variables, functions, and classes. 

The compiler will compile down to x86/x64 assembly and will allow the user to execute their programs on their target machine.

The compiler is composed of these components:
- Lexical Analyzer (Lexer): Takes in source code (custom langage) and returns a list of tokens
- Parser: Takes in list of tokens and returns an AST
- Generator: Takes in our AST and generates ASM code

## User Stories and Design Diagrams

### User Stories
1. As a user, I want my source code to compile into x86/x64 assembly so that I can link,
load, and execute my code.

This is a broad requirement. The goal of this compiler is to take source code in our
language and produce something that can be ran on a machine.

2. As a user, I want the compiler to generate detailed error messages so that I can easily
debug issues with my code.

This requirement pertains to error messages raised throughout the stages in the
compiler. The compiler should be able to tell the user where the error was so that they
can easier locate the error in their code and make the appropriate fix.

3. As a developer, I want the the compiler to handle variable declarations so that users
can perform operations on variable data.

This requirement will allow users to create variables of a specified type. This is an
important feature of any language.

### Design Diagrams
#### Design Diagram 1: Basic Compiler Function

[Image showing Compiler Functions](https://github.com/troxeldj/senior-compiler/blob/master/design-diagrams/design-1.png?raw=true)

The first diagram is simple, but it's important to understand exactly what a compiler does. A
compiler is defined as a program that takes in code in a "source" language (often called
source code), and generates code in another (target) language.
This simple succinctly diagram defines this operation. The next diagrams will get deeper
into how exactly this translation occurs

#### Design Diagram 2: Compiler Stages

[Image showing compiler stages](https://github.com/troxeldj/senior-compiler/blob/master/design-diagrams/design-2.png?raw=true)

Lexical Analysis: Here we scan through characters, group them and output Tokens. A
token is a data structure that contains a value and a type (see diagram 3 for more
detail).
Input: text (file contents)
Output: A list of tokens

Syntax Analysis: Here we work with the tokens output by the lexer. We define a
grammar and can build a parser to parse tokens according to our grammar (the
starting grammar is defined below)
Input: List of Tokens
Output: AST (Abstract Syntax Tree)
Note: Our language will use a "Recursive Descent Parser"

Intermediate Code Generation (optional): During the transition from source code to
target code, a compiler might generate a variety of intermediate representations of our
program before eventually getting to our target code.
Input: AST (Abstract Syntax Tree) or Another Intermediate Representation of our
AST
Output: Intermediate representation of our program

Code Generation: Here is where we use our Abstract Syntax Tree or intermediate
representation to generate code in our target language
Input: AST or intermediate representation of our program
Output: Code in our target language

#### Design Diagram 3: UML Diagram
[Image showing UML Diagram](https://github.com/troxeldj/senior-compiler/blob/master/design-diagrams/design-3.png)

This more-in-depth design goes into the system at a component level. We define classes
used by the various stages

Compiler Components:
- Lexer: The lexer will take in source code, group characters into "lexemes" and make
tokens out of these lexemes and a token type.
- Parser: The parser will take the list of tokens from the lexer, fit them to a grammar
(starting grammar provided - will expand as project goes on).
- Generator: The generator will take the AST generated by the parser, run the
generateProgram method that will traverse this tree, and generate code for the
elements in the tree. The generator will produce assembly code that we can then link, load, and execute on our machine.

Other Classes:
- TokenType (enum): This enum will hold all the token types for the language. The
token has a token type that allows the developer to differentiate between tokens based on their type.
- Token: This class will be used in the lexer to generate a list of tokens based on input
text. It will also be used by the parser to tell what operations are occuring (example: <number> <operator> <number> is a binary operation).
- Expr: Base class for expressions. This abstract class will serve as a base class for other expression types (such as BinaryExpr, UnaryExpr, Literal)

## Project Tasks and Timeline
### Task List

A typical compiler operates in stages, a compiler can have a multitude of different stages. However, for my project there will be four distinct stages:
1. Lexical Analysis
2. Parsing
3. Intermediate code Generation
4. Assembly (x86/x64) Code Generation


#### Lexical Analysis Tasks
1. Research Lexical Analysis and what the purpose of lexical analysis is within a compiler
2. Research implementations of Lexical Analysis Components (Lexers) in current language compilers; such as CPython
3. Develop the lexical analysis component (lexer) of the compiler
4. Test and QA the lexical analysis component(s) of the compiler

#### Parsing Tasks
5. Research Parsing and what the purpose of parsing is within a compiler
6. Research the various types of parsing (recursive descent, top-down, bottom-up, etc.) to find the best fit for the project
7. Research Implementations of Parsing Components (Parsers) in current language compilers; such as CPython
8. Develop the parsing component of the compiler
9. Test and QA the parsing component(s) for the compiler

#### Code Generation Tasks
9. Research Intermediate code generation and common formats compilers use to generate intermediate forms (things such as three-address-code (TACS/3AC)).
10. Research intermediate code generation implementations in current language compilers; such as CPython
11. Develop the intermediate code generation component for the project's compiler
12. Research Assembly Code Generation implementations and how this process works in current compiler implementations; such as CPython
13. Develop the code generation component for the project's compiler

#### Final QA Tasks
14. QA the compiler as a whole. Ensure the interaction between components is functioning and the compiler generates correct assembly code.

Note: I (Dillon Troxell) am the only member of my team (Mightnight squad), so all tasks will be assigned to me.

### Milestone List
1. Basic Lexer Created: Creation of a basic lexer that can lex: identifiers, strings, int,
float, numbers, parenthesis, and mathematical operators

2. Basic Parser Created: Creation of a parser that can parse Binary Expressions, Unary
Expressions, Literals, and Variable Declarations

3. Basic Interpreter Created: Creation of a basic interpreter that walks the AST created by the parser and prints output of expressions

4. Basic Generator Created: Creation of a basic generator that walks the AST created by the parser and generates assembly code for the application. 
Includes research around theory and implementation.

5. Add Function Support: Add the ability for the user to create user-defined functions
within scripts.
- Includes research around theory and implementation
- Would require alterations to lexer, parser, and generator

6. Add Class Support: Add the ability for the user to create user-defined classes within
scripts
- Includes research around theory and implementation
- Would require alterations to lexer, parser, and generator

7. Whole Project QA and Refactor: QA of the whole project, refactors/changes made to:
Lexer, Parser, Generator, Interpreter (if needed)
- Includes Testing every part of compiler, writing test cases, and refactoring compiler
logic where needed

### Effort Matrix

| Milestone | Start Date | End Date |
| --------- | ---------- | -------- |
| Basic Lexer | 9/1/24 | Completed |
| Basic Parser | 9/1/24 | Completed |
| Basic Interpreter | 9/1/24 | Completed |
| Basic Generator | 10/7/24 | 12/1/24 |
| Function Support Added | 12/1/24 | 1/1/24 |
| Class Support Added | 1/1/24 | 2/1/24 |
| Whole Project QA and Refactor | 2/1/24 | 4/1/24 |

## ABET Concerns Essay

