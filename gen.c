#include "defs.h"
#include "data.h"
#include "decl.h"

// Generic code generator
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// Given an AST, generate
// assembly code recursively
int gen_AST(struct ASTnode* n) {
    int leftreg, rightreg;
    if (n->left)
        leftreg = gen_AST(n->left);
    if (n->right)
        rightreg = gen_AST(n->right);
    switch (n->op) {
        case A_ADD:
            return cg_binop(leftreg, rightreg, '+');
        case A_SUBTRACT:
            return cg_binop(leftreg, rightreg, '-');
        case A_MULTIPLY:
            return cg_binop(leftreg, rightreg, '*');
        case A_DIVIDE:
            return cg_binop(leftreg, rightreg, '/');
        case A_INTLIT:
            return cg_load(n->intvalue);
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->op);
            exit(1);
    }
}

void gen_preamble() {
    cg_preamble();
}
void gen_postamble() {
    cg_postamble();
}
void gen_free_regs() {
    free_all_registers();
}
void gen_print_int(int reg) {
    cg_print_register(reg);
}

void generate_code(struct ASTnode* n) {
    int reg;
    cg_preamble();
    reg = gen_AST(n);
    cg_print_register(reg);
    cg_postamble();
}