# jcc (jomo C Compiler)

This is a self-hosting C compiler that is being developed as a pet project to learn more about compilers and the C programming language.

This project is based on the work done in [this repository](https://github.com/DoctorWkt/acwj) and is being developed with the purpose of learning and educational use.

Please note that this project is not intended for production use and is currently in an early stage of development. Use at your own risk.

We welcome any contributions or feedback on this project. If you have any questions or suggestions, please open an issue or pull request on this repository.

# Project structure

main.c handles the overall execution of the compiler. It initializes global variables, checks command line arguments, opens input and output files, and calls the scanfile() function to scan tokens in the input.

scan.c contains functions to scan through the input characters and group them into tokens like identifiers, keywords, operators, etc. It returns the token type and value.

data.h defines global variables used throughout the compiler.

expr.c parses expressions into AST nodes. It handles primary factors, checks operator precedence, and builds the AST recursively.

cg.c generates assembly code from the AST. It handles registers, loads values, performs operations, prints values, stores values, and generates symbols. The functions each generate a part of the assembly output.

gen.c generates assembly code by recursively traversing an AST. It handles the different AST node types by calling functions in cg.c to generate the necessary assembly instructions.

tree.c defines functions to create the different types of nodes in an AST - internal nodes with an operator and two subtrees, leaf nodes, and unary operator nodes with one subtree.