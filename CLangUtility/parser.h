#ifndef PARSER_H
#define PARSER_H

// List of valid LOGO commands
#define VALID_COMMANDS_COUNT 5
//Declares an array of valid LOGO commands.
extern const char *VALID_COMMANDS[VALID_COMMANDS_COUNT];

// Command Structure 

typedef struct {
    char operation[10];
    int degree;
}CommandNode;

typedef struct {
    int repeat_count;
    struct ASTNode *body; // this points to the first node inside REPEAT which is suppose to be executed 
}RepeatNode;

typedef struct{
    enum { COMMAND_NODE, REPEAT_NODE} type;
    union{
        CommandNode command;
        RepeatNode repeat;
    }data;
    struct ASTNode *next;
}ASTNode;



// Function declarations
int validate_tokens(char *tokens[], int token_count);
void to_uppercase(char *str);
int is_number(const char *token); 
int is_bracket(const char *token);

/**
 * Parses a list of tokens into an Abstract Syntax Tree (AST).
 * @param tokens - Array of token strings
 * @param token_count - Total number of tokens
 * @param index - Pointer to an integer tracking the current position in tokens
 * @return Pointer to the root AST node, or NULL if parsing fails
 */
ASTNode *parse_tokens(char *tokens[], int token_count, int *index);

/**
 * Frees the allocated AST structure.
 * @param node - The root node of the AST
 */
void free_ast(ASTNode *node);



#endif