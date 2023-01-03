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
            fprintf(stderr, "Unknown token type %d in get_ast_op\n",
                    token_type);
            exit(1);
    }
}

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode* parse_primary(void) {
    struct ASTnode* n = NULL;
    int id;

    switch (Token.token) {
        case T_INTLIT:
            // For an INTLIT token, make a leaf AST node for it.
            n = create_ast_leaf(A_INTLIT, Token.intvalue);
            break;

        case T_IDENT:
            // Check that this identifier exists
            id = find_glob(Text);
            if (id == -1)
                fatals("Unknown variable", Text);

            // Make a leaf AST node for it
            n = create_ast_leaf(A_IDENT, id);
            break;

        default:
            fatald("Syntax error, token", Token.token);
    }

    // Scan in the next token and return the leaf node
    scan(&Token);
    return (n);
}

// Operator precedence for each token
static int OpPrec[] = {0, 10, 10, 20, 20, 0};

// Check that we have a binary operator and
// return its precedence.
static int op_precedence(int tokentype) {
    int prec = OpPrec[tokentype];
    if (prec == 0) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
        exit(1);
    }
    return (prec);
}

// Return an AST tree for a binary operator expression.
// ptp is the precedence of the previous token.
struct ASTnode* parse_bin_expr(int ptp) {
    // left and right operands of the binary operator
    struct ASTnode *left, *right;
    // the current token's type
    int tokentype;

    // get the left operand
    left = parse_primary();
    // get the current token's type
    tokentype = Token.token;

    // if there are no more tokens, return the left node
    if (tokentype == T_SEMI)
        return (left);

    // while the current token's precedence is greater than the previous token's
    // precedence
    while (op_precedence(tokentype) > ptp) {
        // get the next token
        scan(&Token);
        // Recursively call parse_bin_expr() with the precedence of our token to
        // build a subtree
        right = parse_bin_expr(OpPrec[tokentype]);
        // create a new AST node with the left and right operands as children
        // and the current token's type as the root
        left = create_ast_node(get_ast_op(tokentype), left, right, 0);
        // update the current token's type
        tokentype = Token.token;
        // if there are no more tokens, return the left operand
        if (tokentype == T_SEMI)
            return (left);
    }

    // return the left operand when the current token's precedence is the same
    // or lower
    return (left);
}
