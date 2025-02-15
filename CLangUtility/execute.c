#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "execute.h"


void execute(ASTNode *ast){
    if(ast == NULL){
        printf("No AST to be executed");
        return;
    }
    ASTNode *node = ast;
    while(node ){
        if(node->type == COMMAND_NODE){
            printf("Executing Command: %s %d \n", node->data.command.operation, node->data.command.degree);
        }
        else if(node->type == REPEAT_NODE){
            printf("Executing Command: REPEAT %d times \n", node->data.repeat.repeat_count);
            for (int i=0;i<node->data.repeat.repeat_count;i++){
                printf("\t Iteration %d \n",i+1);
                execute((ASTNode *)node->data.repeat.body);

            }
        }else{
            printf("Invalid Node Type found : %u \n", node->type);
        }
        node = (ASTNode *)node->next;
    }
}