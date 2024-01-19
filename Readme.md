A simplified grammar for basic mathematical expressions:

```
expression  → term ( '+' term | '-' term )*
term        → factor ( '*' factor | '/' factor )*
factor      → base ( '^' exponent )?
base        → number | variable | '(' expression ')'
exponent    → number | variable
number      → integer | decimal
integer     → [0-9]+
decimal     → [0-9]+ '.' [0-9]+
variable    → [a-zA-Z]
```
## Basic Representation
```
variable {
    string name;
}
number {
    float value;
}
exponent {
    number | variable;
}
base {
    number | variable | (expr)
}
factor {
    base 
    exponent?
}
term {
    factor,
    op,
    factor
}

expression {
    term,
    op,
    term
}
```
## Tokens 
```
PLUS      -> '+'
MINUS     -> '-'
DIVIDE    -> '/'
MULTIPLY  -> '*'
POWER     -> '^'
NUMBER    -> [0-9]+
VARIABLE  -> [a-zA-Z]
DOT       -> '.'
LPAREN    -> '('
RPAREN    -> ')'
```

## Non terminals
expression,term,factor,base,exponent,number,integer,decimal,variable


## Axiome  
expression
