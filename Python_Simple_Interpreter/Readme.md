This is the simple interpreter for LOGO language, This focuses on parsing the language and running it directly. 
It might skip the phase of the AST for now 

You can consider it as Single Pass interpretation 


LOGO lang specifications 

1. Simpler Movement Commands: 
    a. FD: Forward 
    b: BK: Backward 
    c. RT: Right 
    d. LT: Left 
2. Command Syntax : FD 40 
3. REPEAT count [ COMMAND]  ex: REPEAT 4 [FD 40 RT 90]




Tokenize phase 
1. Skipping valid syntax right now 
2. Just scanning  the tokens given as it is and converting them into UPPER case for easier parsing 