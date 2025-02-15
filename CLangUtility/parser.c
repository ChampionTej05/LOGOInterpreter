#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"


const char *VALID_COMMANDS[VALID_COMMANDS_COUNT] = {"REPEAT", "FD", "BK", "RT", "LT"};

void to_uppercase(char *str){
    for (int i =0 ; str[i]; i++){
        str[i] = toupper((unsigned char)str[i]);
    }
}

int is_number(const char *token){
    for(int i=0; token[i];i++){
        if(!isdigit((unsigned char)token[i])){
            return 0;
        }
    }

    return 1;
}


int is_bracket(const char *token){
    for(int i=0; token[i];i++){
        if(strcmp("[", &token[i])==0 || 
            strcmp("]", &token[i]) ==0 ){
                return 1;
            }
    }

    return 0;
}


int validate_tokens(char *tokens[], int token_count){

    for (int i=0;i < token_count; i++){
        if(is_number(tokens[i]) || is_bracket(tokens[i])){
            // printf("Skipping validation as token is not operation command");
            continue;
        }

        int token_valid = 0;

        to_uppercase(tokens[i]);

        for ( int j=0; j<VALID_COMMANDS_COUNT; j++){
            if(strcmp(tokens[i], VALID_COMMANDS[j]) == 0){
                // that means match found 
                token_valid =1 ; 
                break;
            }
        }

        // if token never validated 
        if(!token_valid){
            printf("operation in the token does not match with LOGO defined operations");
            return 0;
        }
    }

    return 1;
}