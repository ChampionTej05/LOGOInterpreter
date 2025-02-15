#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKENS 100
#define MAX_TOKEN_SIZE 20 

// Function to tokenize input
void tokenize(const char *input, char *tokens[], int *token_count);

#endif