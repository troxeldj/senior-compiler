program -> (expression)*

expression -> binaryExpr | unaryExpr

binaryExpr -> (term | primary) (+ | -) (term | primary)

unaryExpr -> (+ or -) primary          (like in python, a negative number is i.e -21)

term -> primary (* | /) primary

primary -> (integer_literal | expression) (+ | -) (integer_literal | expression)
 
LL1 - How many lookahead
        - 1 = How many
        - LL = Left associativity
                - L: Scanning input from left to right
                - L (2nd): 
LL1 Grammar if it can be parsed by LL1 parser



Recursive Descent Grammars


Expression -> "let" identifier = Expression

              | Term "+" Term
              
              | Term "-" Term
              
              | Term "*" Term
              | Term "/" Term
              | Term

Term -> identifier
        | number
        | "(" Expression ")"

identifier -> letter (letter | digit)*

number -> digit*

letter -> a-z | A-Z

------------ Revision Will/Dillon 8/16
Program -> (Expr)* | (VarDecl)*

Expr -> BinaryExpr | UnaryExpr | VarDecl | Literal

VarDecl -> Datatype Idenifier "=" Expr

Literal -> string | int | float

Datatype -> "string" | "int" | "float"

Identifier -> [a-zA-Z0-9_]*

BinExpr -> Fact (+ | -) Fact | Fact

UnaryExpr -> (+ | -) Fact 

Fact -> Paren (* | /) Paren | Paren

Paren -> "(" Expr ")" | Term | Identifier

Term -> 1,2,3...

String -> '"' [a-zA-Z_]*


12 * 2 + 10 -> binaryOp




               BinaryOp
               /  |   \
        BinaryOp  +   10
        /  |   \
      12   *    2

                          BinaryOp 
                          /    |   \
                     BinaryOp  +   UnaryOp
                      /   |   \       |
                    12    *    2      10
