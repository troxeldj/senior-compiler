

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

