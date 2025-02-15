#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"  // Include lexer.h to use Token structure

// List of valid LOGO commands
#define VALID_COMMANDS_COUNT 5
//Declares an array of valid LOGO commands.
extern const char *VALID_COMMANDS[VALID_COMMANDS_COUNT];

// Function declarations
int validate_tokens(char *tokens[], int token_count);
void to_uppercase(char *str);

#endif