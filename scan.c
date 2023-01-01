#include "defs.h"
#include "data.h"
#include "decl.h"

// Structure and enum definitions
// Copyright (c) 2019 Warren Toomey, GPL3

// Modification Copyright (c) 2022 Emin, GPL3

// Returns position of the character in the string or -1 if not found
static int find_char(char *s, int c) {
    char *p = strchr(s, c);
    return (p ? p - s : -1);
}

// Get the next character from the input file.
static int get_next_char(void) {
    int c;
    if (Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }
    // InFile is a global variable
    c = fgetc(Infile);
    if (c == '\n')
        Line++;
    return c;
}

// Put back a character that we don't want
static void putback(int c) {
    Putback = c;
}

// Skip past input that we don't need to deal with, i.e. whitespace, newlines.
// Return the first character we do need to deal with.
static int skip(void) {
    int c;
    c = get_next_char();
    while (isspace(c))
        c = get_next_char();
    return c;
}

// Scan and return an integer literal value from the input file. Store the
// value as a string in Text.
static int scanint(int c) {
    int k, val = 0;

    // Convert each character into an int value
    while (isdigit(c)) {
        val = val * 10 + c - '0';
        c = get_next_char();
    }

    // We hit a non-integer character, put it back.
    putback(c);
    return val;
}

// Scan and return the next token found in the input. Return 1 if token valid,
// 0 if no tokens left.
int scan(struct token *t) {
    int c;

    // Skip whitespace
    c = skip();

    // Determine the token based on the input character
    switch (c) {
        case EOF:
            return t->token = T_EOF;
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        default:
            // If it's a digit, scan the literal integer value in
            if (isdigit(c)) {
                t->intvalue = scanint(c);
                t->token = T_INTLIT;
                break;
            }

            fprintf(stderr, "Unrecognised character on line %d: %c\n", Line, c);
            exit(1);
    }

    // We found a token
    return 1;
}