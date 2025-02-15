import re

class LogoInterpreter():
    

    def __init__(self):
        self.pattern = "REPEAT|FD|BK|RT|LT|\d+|\[|\]" 

    def tokensize(self, statement):

        parsed_values = re.findall(self.pattern, statement, re.IGNORECASE)
        tokens = [token.upper().strip() if token.isalpha() else token for token in parsed_values]
        # print(tokens)
        return tokens

    def validate(self):
        # validate the grammer here 
        pass 

    def execute(self, tokens ):
        #assuming grammer stage is passed and expression is valid 
        index = 0 
        instructions = []
        while index < len(tokens):
            if tokens[index] == 'FD':
                instructions.append("Move Forward By ")
                index+=1 
                try:
                    degree = int(tokens[index])
                except ValueError:
                    print("expected integer, got ", tokens[index])
                    return 
                instructions.append("{}\n".format(degree))
           
            
            elif tokens[index] == 'BK':
                instructions.append("Move Backward By ")
                index+=1 
                try:
                    degree = int(tokens[index])
                except ValueError:
                    print("expected integer, got ", tokens[index])
                    return 
                instructions.append("{}\n".format(degree))
               
            elif tokens[index] == 'RT':
                instructions.append("Moved Right By ")
                index+=1 
                try:
                    degree = int(tokens[index])
                except ValueError:
                    print("expected integer, got ", tokens[index])
                    return 
                instructions.append("{}\n".format(degree))
                
            elif tokens[index] == 'LT':
                instructions.append("Move Left By ")
                index+=1 
                try:
                    degree = int(tokens[index])
                except ValueError:
                    print("expected integer, got ", tokens[index])
                    return 
                instructions.append("{}\n".format(degree))
            
            elif tokens[index] == 'REPEAT':
                index+=1 
                # we have now moved to NUMBER 
                try: 
                    repeatation = int(tokens[index])
                    instructions.append("Repeat Instructions for {} \n ".format(repeatation))
                except ValueError:
                    print("Value was supposed to be Integer , got " , tokens[index])
                    return
            
                index+=1 
                #we have moved to "["
                if tokens[index] != '[':
                    print("Exepcted [ at the start of the repeat ")
                    return 
                
                #skip [
                index+=1 

                # collect all the inner statement tokens 
                inner_statement_tokens = []
                while tokens[index]!="]":
                    inner_statement_tokens.append(tokens[index])
                    index+=1 
                for i in range(repeatation):
                    instructions.append(self.execute(inner_statement_tokens))
            index+=1

        print(instructions)
        return instructions
            


                

        





obj = LogoInterpreter()
statement = "REPEAT 4 [FD 40 RT 90]"
tokens = obj.tokensize(statement)
print(tokens)
obj.execute(tokens)