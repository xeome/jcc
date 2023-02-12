#include "defs.h"
#include "data.h"
#include "decl.h"

// Structure and enum definitions
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

// Get the next character from the input file. If putback is true, then we are putting back a character, and we should not get a new one.
static int next(void) {
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
    c = next();
    while (isspace(c))
        c = next();
    return c;
}

// Scan and return an integer literal value from the input file. Store the
// value as a string in Text.
static int scanint(int c) {
    int val = 0;

    // Convert each character into an int value
    while (isdigit(c)) {
        val = val * 10 + c - '0';
        c = next();
    }

    // We hit a non-integer character, put it back.
    putback(c);
    return val;
}

// Scan an identifier from the input file and
// store it in buf[]. Return the identifier's length
static int scanident(int c, char* buf, int lim) {
    int i = 0;

    // Allow digits, alpha and underscores
    while (isalpha(c) || isdigit(c) || '_' == c) {
        // Error if we hit the identifier length limit,
        // else append to buf[] and get next character
        if (lim - 1 == i) {
            fatal("Identifier too long");
        } else if (i < lim - 1) {
            buf[i++] = c;
        }
        c = next();
    }
    // We hit a non-valid character, put it back.
    // NUL-terminate the buf[] and return the length
    putback(c);
    buf[i] = '\0';
    return (i);
}

// Given a word from the input, return the matching
// keyword token number or 0 if it's not a keyword.
// Switch on the first letter so that we don't have
// to waste time strcmp()ing against all the keywords.
static int keyword(char* s) {
    switch (*s) {
        case 'i':
            if (!strcmp(s, "int"))
                return (T_INT);
            break;
        case 'p':
            if (!strcmp(s, "print"))
                return (T_PRINT);
            break;
    }
    return 0;
}

// Scan and return the next token found in the input. Return 1 if token valid,
// 0 if no tokens left.
int scan(struct token* t) {
    int c, tokentype;

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
        case ';':
            t->token = T_SEMI;
            break;

        case '=':
            if ((c = next()) == '=') {
                t->token = T_EQ;
            } else {
                putback(c);
                t->token = T_ASSIGN;
            }
            break;
        case '!':
            if ((c = next()) == '=') {
                t->token = T_NE;
            } else {
                fatalc("Unrecognised character", c);
            }
            break;
        case '<':
            if ((c = next()) == '=') {
                t->token = T_LE;
            } else {
                putback(c);
                t->token = T_LT;
            }
            break;
        case '>':
            if ((c = next()) == '=') {
                t->token = T_GE;
            } else {
                putback(c);
                t->token = T_GT;
            }
            break;
        default:

            // If it's a digit, scan the
            // literal integer value in
            if (isdigit(c)) {
                t->intvalue = scanint(c);
                t->token = T_INTLIT;
                break;
            } else if (isalpha(c) || '_' == c) {
                // Read in a keyword or identifier
                scanident(c, Text, TEXTLEN);

                // If it's a recognised keyword, return that token
                tokentype = keyword(Text);
                if (tokentype) {
                    t->token = tokentype;
                    break;
                }
                // Otherwise, return an identifier token
                t->token = T_IDENT;
                break;
            }
            // The character isn't part of any recognised token, error
            fatalc("Unrecognised character", c);
    }

    // We found a token
    return 1;
}
