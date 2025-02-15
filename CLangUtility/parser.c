#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

ASTNode *parse_tokens(char *tokens[], int token_count, int *index){
    ASTNode *head = NULL, *tail = NULL;

    while(*index < token_count){

        // case 1: REPEAT TOKEN 
        if(strcmp(tokens[*index], "REPEAT")==0){

            // validate if  next token is NUMBER and "[" opening brace
            if( *index+2 >= token_count 
            || !is_number(tokens[*index + 1])
            || strcmp(tokens[*index+2],"[") !=0){
                // i.e if there are not more than two tokens 
                // and next token is not number 
                // and next to next token is not [ --> INVALID 
                printf("Error: Invalid REPEAT syntax\n");
                return NULL;
            }

            // Valid REPEAT syntax , now we need to create Repeat Node 
            
            ASTNode *repeat_node =(ASTNode *) malloc(sizeof(ASTNode));
            repeat_node->data.repeat.repeat_count = atoi(tokens[*index+1]);
            repeat_node->type = REPEAT_NODE;
            repeat_node->data.repeat.body=NULL;
            repeat_node->next= NULL;

            // skip all the parsed tokens above whicparse_tokensh are REPEAT NUM [ 

            *index+=3;

            // Now inside REPEAT, it could be COMMAND or another nested REPEAT, so recursive calls 
            // this will be part of the actual BODY of the top level repeat node 
            repeat_node->data.repeat.body= (struct ASTNode*) parse_tokens(tokens, token_count, index);


            // validate closing ] 

            if(*index >=token_count || strcmp(tokens[*index], "]")!=0){
                printf("Expected ], invalid syntax");
                return NULL;
            }

            // end of parsing for bracket 
            *index+=1;

            // whatever work we have done inside the sub block, we need to attach the linked list to main AST 
            if(head == NULL){
                head = repeat_node;
                tail = repeat_node;
            }
            else{
                tail->next = (struct ASTNode*) repeat_node;
                tail = repeat_node;
            }
            


        }else if (strcmp(tokens[*index], "]") == 0) {
            // Stop parsing when we reach a closing bracket
            // This IMP condition to ensure parser stop once we have finished the top level REPEAT BLOCK 
            return head;
        }
        else{
            // case 2: COMMAND TOKEN 

            // as per LOGO rules, no further nesting of bracket is allowed 
            if (*index + 1 < token_count && strcmp(tokens[*index + 1], "[") == 0) {
                printf("Error: Unexpected '[' after command '%s'\n", tokens[*index]);
                return NULL;
            }

            // Command Node 

            ASTNode *command_node = (ASTNode *) malloc(sizeof(ASTNode));
            command_node->type = COMMAND_NODE;
            strcpy(command_node->data.command.operation, tokens[*index]);
            if(*index+1 < token_count && is_number(tokens[*index+1])){
                command_node->data.command.degree = atoi(tokens[*index+1]);
                command_node->next = NULL;
                *index+=2;
            }else{
                printf("Expected Number after Command ");
                return NULL;
            }
            
            // this should be attached to the parent 

            if(head == NULL){
                head = command_node;
                tail = command_node;
            }else{
                tail->next = (struct ASTNode*)command_node;
                tail = command_node;
            }
        }
        
    }

    return head; 

}

// Free AST memory
void free_ast( ASTNode *node) {
    while (node) {
        ASTNode *temp = node;
        if (node->type == REPEAT_NODE) {
            free_ast(( ASTNode*)node->data.repeat.body);
        }
        node = ( ASTNode*)node->next;
        free(temp);
    }
}