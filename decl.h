// Function prototypes for all compiler files
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

int scan(struct token *t);

struct ASTnode *create_ast_node(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);

struct ASTnode *create_ast_leaf(int op, int intvalue);

struct ASTnode *create_ast_unary(int op, struct ASTnode *left, int intvalue);

struct ASTnode *parse_bin_expr(int ptp);

void free_all_registers(void);

void cg_preamble(void);

void cg_postamble(void);

int cg_load(int value);

int cg_binop(int r1, int r2, int op);

void cg_print_register(int reg);

int interpretAST(struct ASTnode *n);

void generate_code(struct ASTnode *n);
