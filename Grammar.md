## Grammar:

```
entry = stmt* EOF
stmt = (declStmt | printCall) TOK_SEMICOLON
declStmt = dataType TOK_IDENTIFIER TOK_ASSIGN additiveExpr
additiveExpr = multiplicativeExpr ((PLUS | MINUS) multiplicativeExpr)?
multiplicativeExpr = atomicExpr ((MUL | DIV) atomicExpr)?
atomicExpr = constant | TOK_IDENTIFIER | TOK_LPAREN additiveExpr TOK_RPAREN
constant = TOK_INT_LIT | TOK_DOUBLE_LIT
printCall = TOK_PRINT TOK_LPAREN additiveExpr TOK_RPAREN
dataType = TOK_TYPE_INT | TOK_TYPE_DOUBLE
```

## Tokens:

```
TOK_INVALID
TOK_INT_LIT
TOK_DOUBLE_LIT
TOK_IDENTIFIER
TOK_TYPE_INT
TOK_TYPE_DOUBLE
TOK_PRINT
TOK_ASSIGN
TOK_PLUS
TOK_MINUS
TOK_MUL
TOK_DIV
TOK_LPAREN
TOK_RPAREN
TOK_SEMICOLON
TOK_EOF
```