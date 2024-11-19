/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] Abbey Hankins
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"


/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	char line[MAX_LINE_LENGTH] = "";
	char label[MAX_LABEL_LENGTH] = {0};
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	

	while (fgets(line, sizeof(line), file)){
		line_num++;

		if (instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		strip(line);
		
		//printf("[%04d] %s", line_num, line);

		//if line is not blank, print the line
		if (!*line){
			continue;
		}
		
		char inst_type;

	if (is_Atype(line)) {
    	inst_type = 'A';
		
	} 
	else if (is_label(line)) {
    	inst_type = 'L';
		extract_label(line, label);

		if(!isalpha(line[1])){
			exit_program(EXIT_INVALID_LABEL, line_num, line);
		}

		if (symtable_find(label) != NULL){
			exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
		}

		strcpy(line, label);
		//printf("Label '%s' on line %d\n", label, line_num);
		symtable_insert(label,instr_num);
		
		//TODO maybe line_num--
		continue;
	} 
	else if (is_Ctype(line)) {
    	inst_type = 'C';
		
	}

	printf("%u: %c  %s\n", instr_num, inst_type, line);
	instr_num++;
	}

}

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	char s_new[strlen(s) + 1];
	int i = 0; 

	for (char *s2 = s; *s2; s2++ ){
		if ((*s2 == '/') && (*(s2+1) == '/')){
			break; 
		}
		
		if(!isspace(*s2)){
			s_new[i++] = *s2;
		}
	}

	s_new[i] = '\0';
	strcpy(s, s_new);
    return s;	
}


bool is_Atype(const char *line){

	if (line[0] == '@'){
		return true;
	}
	else{
		return false;
	}
}

bool is_label(const char *line){
	
	if ((line[0] == '(') && line[strlen(line) - 1] == ')'){
		return true;
	}
	else{
		return false;
	}
}

bool is_Ctype(const char *line){
	if (is_Atype(line) == false && is_label(line)==false){
		return true;
	}
}
 
char *extract_label(const char *line, char* label){
	const char *first = line +1; //Points to the first character of the label name
	const char *last = line + strlen(line) - 1; //points to the last 

	int length = last - first; // length of label 


	//copies every letter from label input and puts it in the label 
	for (int i = 0; i <length; i++ ){
		label[i] = first[i];
	}

	label[length] = '\0';

	return label; 
}

