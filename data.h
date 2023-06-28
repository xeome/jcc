#ifndef extern_
#define extern_ extern
#endif

// Global variables
// Copyright (c) 2019 Warren Toomey, GPL3

extern_ int Line;                        // Current line number
extern_ int Putback;                     // Putback character
extern_ FILE* inputFile;                 // Input file handle
extern_ FILE* Outfile;                   // Output file handle
extern_ struct token Token;              // Current token
extern_ char Text[TEXTLEN + 1];          // Last identifier scanned
extern_ struct symtable Gsym[NSYMBOLS];  // Global symbol table