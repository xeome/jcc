// Function prototypes for all compiler files
// Copyright (c) 2019 Warren Toomey, GPL3
int scan(struct token *t);

struct ASTnode *create_ast_node(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);

struct ASTnode *create_ast_leaf(int op, int intvalue);

struct ASTnode *create_ast_unary(int op, struct ASTnode *left, int intvalue);

struct ASTnode *parse_bin_expr(int ptp);

int interpretAST(struct ASTnode *n);