/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Abbey Hankins
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"

int main(int argc, const char *argv[])
{		
	if (argc != 2){
		// incorrect number of arguments
    	exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);   
	}

FILE *fin = fopen(argv[1], "r");

	if (fin == NULL){
		// incorrect number of arguments
    	exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);   
	}

parse(fin);
fclose(fin);
}


