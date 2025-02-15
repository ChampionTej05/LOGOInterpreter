This is follows the standard paradigm of the Compiler / Interpreter design principle regarding LOGO 

Where each phase ensures that next phase should make the next phase simpler to process 


1. Lexer (Scanning ): Create Tokens for the Parser 
2. Parser (Static Analysis and AST Creation): Validate the tokens, grammer and create AST out of it 
3. Execution : AST Walk 