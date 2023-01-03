#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of statements
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// statements: statement
//      |      statement statements
//      ;
//
// statement: 'print' expression ';'
//      |     'int'   identifier ';'
//      |     identifier '=' expression ';'
//      ;
//
// identifier: T_IDENT
//      ;

void print_statement(void) {
    struct ASTnode* tree;
    int reg;

    // Match a 'print' as the first token
    match(T_PRINT, "print");

    // Parse the following expression and
    // generate the assembly code
    tree = parse_bin_expr(0);
    reg = gen_AST(tree, -1);
    gen_print_int(reg);
    gen_free_regs();

    // Match the following semicolon
    semi();
}

void assignment_statement(void) {
    struct ASTnode *left, *right, *tree;
    int id;

    // Ensure we have an identifier
    ident();

    // Check it's been defined then make a leaf node for it
    if ((id = find_glob(Text)) == -1) {
        fatals("Undeclared variable", Text);
    }
    right = create_ast_leaf(A_LVIDENT, id);

    // Ensure we have an equals sign
    match(T_EQUALS, "=");

    // Parse the following expression
    left = parse_bin_expr(0);

    // Make an assignment AST tree
    tree = create_ast_node(A_ASSIGN, left, right, 0);

    // Generate the assembly code for the assignment
    gen_AST(tree, -1);
    gen_free_regs();

    // Match the following semicolon
    semi();
}

// Parse one or more statements
void statements(void) {
    while (1) {
        switch (Token.token) {
            case T_PRINT:
                print_statement();
                break;
            case T_INT:
                var_declaration();
                break;
            case T_IDENT:
                assignment_statement();
                break;
            case T_EOF:
                return;
            default:
                fatald("Syntax error, token", Token.token);
        }
    }
}