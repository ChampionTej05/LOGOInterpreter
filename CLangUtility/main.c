#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "execute.h"
#include "dump_ast.c"

int main(){

    // char input[100];
    // printf("Enter LOGO statement : ");
    // fgets(input, sizeof(input), stdin);

    // printf("%s \n", input);

    // char input[] = "REPEAT 4 [ FD 50 RT 90 ]";
    char input[] = "REPEAT 1 [ FD 90 RT 90 ] LT 30 RT 50 REPEAT 2 [ FD 30 ]";
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
    // ASTNode *node = ast;
    // while (node) {
    //     if (node->type == COMMAND_NODE) {
    //         printf("COMMAND: %s %d\n", node->data.command.operation, node->data.command.degree);
    //     } else {
    //         printf("REPEAT: %d times\n", node->data.repeat.repeat_count);
    //         ASTNode *sub = (ASTNode*) node->data.repeat.body;
    //         while (sub) {
    //             printf("  -> COMMAND: %s %d\n", sub->data.command.operation, sub->data.command.degree);
    //             sub = (ASTNode *) sub->next;
    //         }
    //     }
    //     node = (ASTNode *) node->next;
    // }



    execute(ast);

    // Dump AST to a file
    FILE *out = fopen("ast_output.json", "w");
    if (!out) {
        perror("Error opening file");
        return 1;
    }

    dump_ast_json(ast, out);
    fclose(out);


    free_ast(ast);


    return 0;
}

/**
 * Tokens:
Token 0: REPEAT
Token 1: 1
Token 2: [
Token 3: FD
Token 4: 90
Token 5: RT
Token 6: 90
Token 7: ]
Token 8: LT
Token 9: 30
Token 10: RT
Token 11: 50
Token 12: REPEAT
Token 13: 2
Token 14: [
Token 15: FD
Token 16: 30
Token 17: ]

 Tokens are validated 
 Executing Command: REPEAT 1 times 
	 Iteration 1 
Executing Command: FD 90 
Executing Command: RT 90 
Executing Command: LT 30 
Executing Command: RT 50 
Executing Command: REPEAT 2 times 
	 Iteration 1 
Executing Command: FD 30 
	 Iteration 2 
Executing Command: FD 30 
 */