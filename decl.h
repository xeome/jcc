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
int gen_AST(struct ASTnode* n, int reg);
void gen_preamble(void);
void gen_postamble(void);
void gen_free_regs(void);
void gen_print_int(int reg);
void gen_glob_sym(char* s);

// cg.c
void free_all_registers(void);
void cg_preamble(void);
void cg_postamble(void);
int cg_load_int(int value);
int cg_binop(int r1, int r2, int op);
void cg_print_int(int reg);
int cg_load_glob(char* id);
int cg_store_glob(int r, char* id);
void cg_glob_sym(char* id);
int cg_equal(int r1, int r2);
int cg_not_equal(int r1, int r2);
int cg_less_than(int r1, int r2);
int cg_greater_than(int r1, int r2);
int cg_less_equal(int r1, int r2);
int cg_greater_equal(int r1, int r2);


// expr.c
struct ASTnode* parse_bin_expr(int ptp);

// stmt.c
void statements(void);

// misc.c
void match(int t, char *what);
void semi(void);
void ident(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

// sym.c
int find_glob(char *s);
int add_glob(char *name);

// decl.c
void var_declaration(void);