#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of statements
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// statements: statement
//      | statement statements
//      ;
//
// statement: 'print' expression ';'
//      ;


// Parse one or more statements
void statements(void) {
    struct ASTnode *tree;
    int reg;

    while (1) {
        // Match a 'print' as the first token
        match(T_PRINT, "print");

        // Parse the following expression and
        // generate the assembly code
        tree = parse_bin_expr(0);
        reg = gen_AST(tree);
        gen_print_int(reg);
        gen_free_regs();

        // Match the following semicolon
        // and stop if we are at EOF
        semi();
        if (Token.token == T_EOF)
            return;
    }
}