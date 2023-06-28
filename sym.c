#include "defs.h"
#include "data.h"
#include "decl.h"

// Symbol table management functions
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification (c) 2022 Emin, GPL3

static int global_amount = 0;  // Position of next free global symbol slot

// Determine if the symbol s is in the global symbol table.
// Return its slot position or -1 if not found.
int find_glob(char* s) {
    int i;

    for (i = 0; i < global_amount; i++)
        if (strcmp(Gsym[i].name, s) == 0)
            return (i);
    return (-1);
}

// Get the position of a new global symbol slot, or die if we've run out of
// positions.
static int new_glob(void) {
    if (global_amount >= NSYMBOLS)
        fatal("Out of global symbol space");
    return (global_amount++);
}

// Add a global symbol to the symbol table. Return the slot number in the symbol
// table.
int add_glob(char* name) {
    int i;

    // See if it's already in the symbol table
    if ((i = find_glob(name)) != -1)
        return (i);

    // Otherwise, get a new slot in the symbol table
    i = new_glob();
    Gsym[i].name = strdup(name);
    return (i);
}