from parser import CommandNode, RepeatNode
import turtle
class LogoExecute():


    def __init__(self, AST):
        self.AST = AST 

    def execute(self):
        
        index = 0 
        # print(len(self.AST))
        while index < len(self.AST):
            # take each NODE of the AST and execute them based on the type
            if isinstance(self.AST[index], CommandNode):
                # command, execute it directly using whatever parser we want to 
                # helper function can be used to decide what action to take based on the command 
                self.execute_command(self.AST[index])
            elif isinstance(self.AST[index], RepeatNode):
                node = self.AST[index]
                for i in range(node.repeat):
                    for command in node.commands:
                        # helper function to execute command 
                        self.execute_command(command) 


            index+=1 

    def execute_command(self, node ):
        print("executing the node ")
        if node.operation == "FD":
            # turtle.forward(node.degree)
            print(node)
        elif node.operation == "BK":
            # turtle.backward(node.degree)
            print(node)
        elif node.operation == "RT":
            # turtle.right(node.degree)
            print(node)
        elif node.operation == "LT":
            # turtle.left(node.degree)
            print(node)

        

# turtle.speed(4)

# print(AST)

# obj = LogoExecute(AST)

# obj.execute()

# turtle.mainloop()