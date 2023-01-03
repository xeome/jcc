#include "defs.h"
#include "data.h"
#include "decl.h"

// Generic code generator
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// Given an AST, generate
// assembly code recursively
int gen_AST(struct ASTnode* n, int reg) {
    int leftreg, rightreg;
    if (n->left)
        leftreg = gen_AST(n->left, -1);
    if (n->right)
        rightreg = gen_AST(n->right, leftreg);
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
            return (cg_load_int(n->v.intvalue));
        case A_IDENT:
            return (cg_load_glob(Gsym[n->v.id].name));
        case A_LVIDENT:
            return (cg_store_glob(reg, Gsym[n->v.id].name));
        case A_ASSIGN:
            return rightreg;
        default:
            fatald("Unknown AST operator", n->op);
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
    cg_print_int(reg);
}

void gen_glob_sym(char* s) {
    cg_glob_sym(s);
}