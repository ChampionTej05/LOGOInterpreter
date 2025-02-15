#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "execute.h"

int main(){

    // char input[100];
    // printf("Enter LOGO statement : ");
    // fgets(input, sizeof(input), stdin);

    // printf("%s \n", input);

    char input[] = "REPEAT 4 [ FD 50 RT 90 ]";
    char *tokens[MAX_TOKENS];
    int token_count=0;

    tokenize(input, tokens, &token_count);
    // Print tokens
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        // free(tokens[i]);  // Free allocated memory
    }

    
    int token_valid = validate_tokens(tokens, token_count);
    if (!token_valid){
        return 1;
    }

    printf("\n Tokens are validated \n ");

    // keep track of token parsing 
    int index =0 ;

    ASTNode *ast = parse_tokens(tokens, token_count, &index);
    if(ast == NULL || !ast ){
        printf("AST Parsing Failed .. ");
        return 1;
    }

    // Print AST
    ASTNode *node = ast;
    while (node) {
        if (node->type == COMMAND_NODE) {
            printf("COMMAND: %s %d\n", node->data.command.operation, node->data.command.degree);
        } else {
            printf("REPEAT: %d times\n", node->data.repeat.repeat_count);
            ASTNode *sub = (ASTNode*) node->data.repeat.body;
            while (sub) {
                printf("  -> COMMAND: %s %d\n", sub->data.command.operation, sub->data.command.degree);
                sub = (ASTNode *) sub->next;
            }
        }
        node = (ASTNode *) node->next;
    }

    free_ast(ast);


    return 0;
}