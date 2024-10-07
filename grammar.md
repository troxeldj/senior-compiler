Revision Will/Dillon 8/16
--
Program -> (Expr)*
VarDecl -> Datatype Identifier "=" Expr
Expr = BinaryExpr | UnaryExpr | VarDecl 
Literal -> Datatype Expr
Datatype -> "string" | "int" | "float"
Identifier -> [a-zA-Z0-9_]*
BinaryExpr -> Fact (+ | -) Fact | Fact
UnaryExpr -> (+ | -) Fact
Fact -> Paren (* | /) Paren | Paren
Paren -> "(" Expr ")" | Term | Identifier
Term -> 1,2,3...
String -> '"' [a-zA-Z_]*

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
