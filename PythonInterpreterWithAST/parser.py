class ASTNode():
    def __init__(self):
        pass

class CommandNode(ASTNode):

    def __init__(self, operation:str, degree:int):
        super().__init__()
        self.operations = operation
        # degree needs to be integer so before this should we validate the grammer and make sure everything is as per grammer
        self.degree = degree 


class RepeatNode(ASTNode):

    def __init__(self, commands:list[CommandNode], repeat:int):
        super().__init__()
        self.repeat = repeat 
        # List of CommandNode
        self.commands = commands 

    


class LogoParser():

    def __init__(self, tokens):
        self.tokens = tokens

    def parse(self):
        AST = []

        index = 0 
        while index < len(self.tokens):
            try: 
                if self.tokens[index] in ["FD", "BK", "RT", "LT"]:
                    # operation should be string 
                    if not isinstance(self.tokens[index], str):
                        raise TypeError("Expected String got ", self.tokens[index])
                    operation = str(self.tokens[index])

                    # get the degree 
                    index+=1 
                    #degree should be integer 
                    if not isinstance(self.tokens[index], int):
                        raise TypeError("Expected Integer degree, got ", self.tokens[index])
                    degree = int(self.tokens[index])
                    commandNode = CommandNode(operation, degree)
                    AST.append(commandNode)

                elif self.tokens[index]== 'REPEAT':
                    
                    #get the count 
                    index+=1
                    repeat = int(self.tokens[index])

                    # validate the start of inner body 
                    index+=1
                    if self.tokens[index] != "[":
                        raise TypeError("Expected [ for the start of the REPEAT inner body")

                    #start of inner commands by skipping over [
                    index+=1
                    inner_command_nodes = []
                    for i in range(repeat):
                        commandNode = self.parse()
                        index+=1 
                        # how to parse inner loop without attaching tokens to the function 
                        # we can add tokens to each function and then return AST 
                        # or we can have single parse function and then let it run using SELF CURSOR maintained in the main object class
                    pass

                index+=1


            except Exception as e:
                print("Caught Parsing error ",e )
                return e 


