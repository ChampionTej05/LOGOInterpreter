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

    return 0;
}