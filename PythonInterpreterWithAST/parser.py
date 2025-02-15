class ASTNode():
    def __init__(self):
        pass

class CommandNode(ASTNode):

    def __init__(self, operation:str, degree:int):
        super().__init__()
        self.operation = operation
        # degree needs to be integer so before this should we validate the grammer and make sure everything is as per grammer
        self.degree = degree 

    def __repr__(self):
        return f"{self.operation} {self.degree}"


class RepeatNode(ASTNode):

    def __init__(self, commands:list[CommandNode], repeat:int):
        super().__init__()
        self.repeat = repeat 
        # List of CommandNode
        self.commands = commands 

    def __repr__(self):
        return f"REPEAT {self.repeat} {self.commands}"

    


class LogoParser():

    def __init__(self, tokens):
        self.tokens = tokens
        self.cursor = 0 # keeps track of current token being parsed 

    def parse(self):
        AST = []

        while self.cursor < len(self.tokens):
            node = self.parse_command()
            if node :
                AST.append(node)
            return AST


    def parse_command(self):
        try: 
            if self.tokens[self.cursor] in ["FD", "BK", "RT", "LT"]:
                # operation should be string 
                if not isinstance(self.tokens[self.cursor], str):
                    raise TypeError("Expected String got ", self.tokens[self.cursor])
                operation = str(self.tokens[self.cursor])

                # get the degree 
                self.cursor+=1 
                #degree should be integer 
                if not int(self.tokens[self.cursor]):
                    raise TypeError("Expected Integer degree, got ", self.tokens[self.cursor])
                degree = int(self.tokens[self.cursor])
                commandNode = CommandNode(operation, degree)
                self.cursor+=1
                return commandNode

            elif self.tokens[self.cursor]== 'REPEAT':
                
                #get the count 
                self.cursor+=1
                repeat = int(self.tokens[self.cursor])

                # validate the start of inner body 
                self.cursor+=1
                if self.tokens[self.cursor] != "[":
                    raise TypeError("Expected [ for the start of the REPEAT inner body")

                #start of inner commands by skipping over [
                self.cursor+=1
                inner_command_nodes = []
                while self.tokens[self.cursor] != ']':
                    # while we are not at end of stream 
                    commandNode = self.parse_command()
                    inner_command_nodes.append(commandNode)

                self.cursor+=1
                repeatNode = RepeatNode(inner_command_nodes, repeat)
                return repeatNode
            else: 
                raise ValueError("Unexpected Token, ", self.tokens[self.cursor])
                


        except Exception as e:
            print("Caught Parsing error ",e )
            return e 
        



# tokens = ['REPEAT', '4', '[', 'FD', '40', 'RT', '90', ']']

# obj = LogoParser(tokens)

# AST = obj.parse()
# print(len(AST))


