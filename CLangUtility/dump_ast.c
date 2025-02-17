#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"  // Contains the AST definitions

// Forward declaration
void dump_node_json(const ASTNode *node, FILE *out, int indent);

void dump_ast_json(const ASTNode *root, FILE *out) {
    fprintf(out, "{\n");
    fprintf(out, "  \"ast\": [\n");
    const ASTNode *current = root;

    int first_node = 1; // For comma handling
    while (current) {
        if (!first_node) {
            fprintf(out, ",\n");
        }
        dump_node_json(current, out, 4); // Indent by 4 spaces
        first_node = 0;
        current = (ASTNode * )current->next;
    }

    fprintf(out, "\n  ]\n");
    fprintf(out, "}\n");
}

void dump_node_json(const ASTNode *node, FILE *out, int indent) {
    // Helper function to indent
    for (int i = 0; i < indent; i++) {
        fprintf(out, " ");
    }

    if (node->type == COMMAND_NODE) {
        // Print command node as JSON
        fprintf(out, "{ \"type\": \"COMMAND_NODE\", \"operation\": \"%s\", \"degree\": %d }",
            node->data.command.operation,
            node->data.command.degree
        );
    } else if (node->type == REPEAT_NODE) {
        // Print repeat node
        fprintf(out, "{ \"type\": \"REPEAT_NODE\", \"repeat_count\": %d, \"body\": [\n", 
            node->data.repeat.repeat_count
        );
        
        // Recursively dump the body commands
        const ASTNode *bodyNode = (ASTNode * ) node->data.repeat.body;
        int first = 1;
        while (bodyNode) {
            if (!first) {
                fprintf(out, ",\n");
            }
            dump_node_json(bodyNode, out, indent + 2);
            first = 0;
            bodyNode = (ASTNode * )bodyNode->next;
        }

        fprintf(out, "\n");
        for (int i = 0; i < indent; i++) {
            fprintf(out, " ");
        }
        fprintf(out, "] }");
    }
}
