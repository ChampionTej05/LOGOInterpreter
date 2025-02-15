#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

void tokenize(const char *input, char *tokens[], int *token_count) {

    
    // copy input for safety 

    char *input_copy = strdup(input);
    if ( input_copy == NULL){
        printf("Failed to allocate memory ");
        return;
    }

    char *seperator = " ";
    char *token = strtok(input_copy, seperator);
    *token_count = 0 ;  
    while ( token != NULL && *token_count < MAX_TOKENS){
        // memory allocation for the token 

        tokens[*token_count] = strdup(token);
        if (tokens[*token_count] == NULL){
            printf("Failed to allocate memory ");
            free(input_copy);
            return;
        }
        (*token_count)+=1;

        token = strtok(NULL, seperator);

    }

    free(input_copy);
}