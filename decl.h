// Function prototypes for all compiler files
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// scan.c
int scan(struct token* t);

// tree.c
struct ASTnode* create_ast_node(int op,
                                struct ASTnode* left,
                                struct ASTnode* right,
                                int intvalue);
struct ASTnode* create_ast_leaf(int op, int intvalue);
struct ASTnode* create_ast_unary(int op, struct ASTnode* left, int intvalue);

// gen.c
int gen_AST(struct ASTnode* n);
void gen_preamble(void);
void gen_postamble(void);
void gen_free_regs(void);
void gen_print_int(int reg);

// cg.c
void free_all_registers(void);
void cg_preamble(void);
void cg_postamble(void);
int cg_load(int value);
int cg_binop(int r1, int r2, int op);
void cg_print_register(int reg);

// expr.c
struct ASTnode* parse_bin_expr(int ptp);

// stmt.c
void statements(void);

// misc.c
void match(int t, char* what);
void semi(void);