/****************************************
 * C-ploration 4 for CS 271
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

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LABEL_LENGTH - 2)
#define typedef int16_t hack_addr;
#define int16_t opcode; 

/** function prototypes **/
char *strip(char *s);

char *extract_label(const char *line, char* label);

void parse(FILE * file);

bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);
