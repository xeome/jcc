#include "defs.h"
#include "data.h"
#include "decl.h"

// Code generator for x86-64
// Copyright (c) 2019 Warren Toomey, GPL3
// Modification Copyright (c) 2022 Emin, GPL3

#define NUM_REGS 4

// Array of available registers
// and their names
static struct {
    int is_available;
    char *name;
} regs[NUM_REGS] = {
        { .is_available = 1, .name = "%r8" },
        { .is_available = 1, .name = "%r9" },
        { .is_available = 1, .name = "%r10" },
        { .is_available = 1, .name = "%r11" },
};

// Set all registers as available
void free_all_registers(void) {
    for (int i = 0; i < NUM_REGS; i++) {
        regs[i].is_available = 1;
    }
}

// Allocate a free register. Return the number of
// the register. Die if no available registers.
static int alloc_register(void) {
    for (int i = 0; i < NUM_REGS; i++) {
        if (regs[i].is_available) {
            regs[i].is_available = 0;
            return i;
        }
    }
    fprintf(stderr, "Out of registers!\n");
    exit(1);
}

// Return a register to the list of available registers.
// Check to see if it's not already there.
static void free_register(int reg) {
    if (regs[reg].is_available != 0) {
        fprintf(stderr, "Error trying to free register %d\n", reg);
        exit(1);
    }
    regs[reg].is_available = 1;
}

// Print out the assembly preamble
void cg_preamble() {
    free_all_registers();
    fputs("\t.text\n"
          ".LC0:\n"
          "\t.string\t\"%d\\n\"\n"
          "printint:\n"
          "\tpushq\t%rbp\n"
          "\tmovq\t%rsp, %rbp\n"
          "\tsubq\t$16, %rsp\n"
          "\tmovl\t%edi, -4(%rbp)\n"
          "\tmovl\t-4(%rbp), %eax\n"
          "\tmovl\t%eax, %esi\n"
          "\tleaq	.LC0(%rip), %rdi\n"
          "\tmovl	$0, %eax\n"
          "\tcall	printf@PLT\n"
          "\tnop\n"
          "\tleave\n"
          "\tret\n"
          "\n"
          "\t.globl\tmain\n"
          "\t.type\tmain, @function\n"
          "main:\n"
          "\tpushq\t%rbp\n"
          "\tmovq	%rsp, %rbp\n",
          Outfile);
}

// Print out the assembly postamble
void cg_postamble() {
    fputs("\tmovl	$0, %eax\n"
          "\tpopq	%rbp\n"
          "\tret\n",
          Outfile);
}

// Load an integer literal value into a register.
// Return the number of the register
int cg_load(int value) {

    // Get a new register
    int r = alloc_register();

    // Print out the code to initialize it
    fprintf(Outfile, "\tmovq\t$%d, %s\n", value, regs[r].name);
    return r;
}

// Perform a binary operation on two registers and return
// the number of the register with the result
int cg_binop(int r1, int r2, int op) {
    char *instr;

    // Determine the assembly instruction to use based on the opcode
    switch (op) {
        case '+':
            instr = "addq";
            break;
        case '-':
            instr = "subq";
            break;
        case '*':
            instr = "imulq";
            break;
        case '/':
            instr = "idivq";
            break;
        default:
            fprintf(stderr, "Invalid binary operator: %c\n", op);
            exit(1);
    }

    // Print out the code to perform the operation
    fprintf(Outfile, "\t%s\t%s, %s\n", instr, regs[r1].name, regs[r2].name);
    free_register(r1);
    return r2;
}

// Print out the assembly to print out a register value
void cg_print_register(int r) {
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", regs[r].name);
    fputs("\tcall\tprintint\n", Outfile);
}

