#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of declarations
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// Parse the declaration of a variable
void var_declaration(void) {
    // Ensure we have an 'int' token followed by an identifier
    // and a semicolon. Text now has the identifier's name.
    // Add it as a known identifier
    match(T_INT, "int");
    ident();
    add_glob(Text);
    gen_glob_sym(Text);
    semi();
}