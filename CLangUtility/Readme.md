We have already implemented the parser in Python language, but it very abstracted using the high level language features. 
Let us try doing the same in C language 


First Phase: 
- Get the statement as input string and seperate them into tokens
- for sake of simplicity let us make it always SPACE separable 
- We would store the statement into INPUT char array 


Second Phase: 
- Validate tokens against commands 
- Create  data structure to hold the AST from token 
    - Here to store simple command like FD 50 ,we can simple struct 
    - To store REPEAT 4 [ FD 50  REPEAT 5 [ FD 8 RT 90]] we need struct that can store count and generic structure of either type of command i.e repeat or command type 
    - So using union would make sense 

    CommandNode{operation, degree}
    RepeatNode{repeat_count, AST *body} // this body is head pointer to all the command nested under current repeat node 
    AST{ node_type, union(CommandNode, RepeatNode) data, AST *next} // this AST node now represents generic node which can store any type of node in linked list format ( we can not use array to store as we do not know how many commands are nested)

    - So for REPEAT 4 [ FD 50  REPEAT 5 [ FD 8 RT 90]] 
        - AST{type=repeat, data.Repeatnode.repeat=4, data.repeatnode.body=null, next = null} -> S1
        - then inside of the first REPEAT would sub command node: AST{type=command, data.commandnode.operation=FD, data.commandnode.degree=50, next= null} -> S2 : subhead = S2 
            
        - then insider again REPEAT node : AST(repeat = REPEAT, data.repeatnode.repeat=5, data.repeatnode.body=null, next=null ) -> S3
            - because of S3 . now S2.next = S3 
        - AST { type=command, data.commandnode.operation=Fd, data.commandnode.degree=8, next=null} -> S4
            - S3.next = S4 
        - AST { type=command, data.commandnode.operation=RT, data.commandnode.degree=8=90, next=null} -> S5
            - S4.next = S5 
        - After everything finishes. S1.next = null because there is no sequential block after outer repeat else if we had somethign like REPEAT 4 [ FD 50  REPEAT 5 [ FD 8 RT 90]]  FD 8 , S1.next = AST(fd, 8)