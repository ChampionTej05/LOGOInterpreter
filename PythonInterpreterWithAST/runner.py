from execute import LogoExecute
from parser import LogoParser 
from lexer import LogoLexer 


# statement = "REPEAT 1 [ FD 90 RT 90] LT 30 RT 50 REPEAT 2 [FD 30]"
statement = "REPEAT 1 [ FD 90 RT 90]"

tokens = LogoLexer(statement).tokenize()
print("Tokens ", tokens)
ast_tree = LogoParser(tokens).parse()
print("AST Tree", ast_tree)
LogoExecute(ast_tree).execute()