#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of expressions
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// Convert a token into an AST operation
static int get_ast_op(int token_type) {
    // Return the corresponding AST operation for the given token type
    switch (token_type) {
        case T_PLUS:
            return (A_ADD);
        case T_MINUS:
            return (A_SUBTRACT);
        case T_STAR:
            return (A_MULTIPLY);
        case T_SLASH:
            return (A_DIVIDE);
        case T_INTLIT:
            return (A_INTLIT);
        default:
            fprintf(stderr, "Unknown token type %d in get_ast_op\n", token_type);
            exit(1);
    }
}

// Parse a primary factor and return an AST node representing it.
static struct ASTnode *parse_primary(void) {
    struct ASTnode *n;

    // For an INTLIT token, make a leaf AST node for it and scan in the next token.
    // Otherwise, print a syntax error message and exit the program.
    switch (Token.token) {
        case T_INTLIT:
            n = create_ast_leaf(A_INTLIT, Token.intvalue);
            scan(&Token);
            return (n);
        default:
            fprintf(stderr, "Syntax error on line %d\n", Line);
            exit(1);
    }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *parse_bin_expr(void) {
    struct ASTnode *n, *left, *right;
    int nodetype;

    // Get the integer literal on the left. This is the left subtree of the tree.
    left = parse_primary();

    // If no tokens left, return just the left node
    if (Token.token == T_EOF)
        return (left);

    // Convert the token into a node type
    nodetype = get_ast_op(Token.token);

    // Get the next token in
    scan(&Token);

    // Recursively get the right-hand tree
    right = parse_bin_expr();

    // Now build a tree with both sub-trees
    n = create_ast_node(nodetype, left, right, 0);
    return (n);
}
