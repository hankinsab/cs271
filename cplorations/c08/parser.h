/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Abbey Hankins
 * [TERM] FALL 2024
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef __PARSER_H__
#define __PArSER_H__

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS


typedef int16_t hack_addr;
typedef int16_t opcode; 

/** function prototypes **/
enum instr_type{
    Invalid = -1, 
    A_type, C_type
};

typedef struct c_instruction{
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
} c_instruction;

typedef struct a_instruction{
    union{
        hack_addr address; 
        char * label; 
    };

    bool is_addr;
} a_instruction;

typedef struct instruction{
    union{
        a_instruction a;
        c_instruction c;
    };
    enum instr_type type;
}instruction;

char *strip(char *s);

char *extract_label(const char *line, char* label);

void parse(FILE * file);

bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

#endif
