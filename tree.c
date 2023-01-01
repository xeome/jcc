#include "defs.h"
#include "data.h"
#include "decl.h"

// AST tree functions
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// Given an operator and two AST subtrees, return an AST tree with that operator in the root.
// The integer value is only used for A_INTLIT operators.
struct ASTnode *create_ast_node(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) {
    // Malloc a new ASTnode
    struct ASTnode *n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
    if (n == NULL) {
        fprintf(stderr, "Unable to malloc in create_ast_node\n");
        exit(1);
    }

    // Set up the contents
    n->op = op;
    n->left = left;
    n->right = right;
    n->intvalue = intvalue;

    return n;
}

// Build and return an AST leaf node
struct ASTnode *create_ast_leaf(int op, int intvalue) {
    return (create_ast_node(op, NULL, NULL, intvalue));
}

// Build and return an AST unary operator node
struct ASTnode *create_ast_unary(int op, struct ASTnode *left, int intvalue) {
    return (create_ast_node(op, left, NULL, intvalue));
}



