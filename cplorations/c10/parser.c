/****************************************
 * C-ploration 10 for CS 271
 * 
 * [NAME] Abbey Hankins
 * [TERM] FALL 2024
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"



/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
int parse(FILE * file, instruction *instructions){
	char line[MAX_LINE_LENGTH] = "";
	char label[MAX_LABEL_LENGTH] = {0};
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	instruction instr;
	char tmp_line[MAX_LINE_LENGTH];

	
	add_predefined_symbols();

	while (fgets(line, sizeof(line), file)){
		line_num++;

		if (instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		strip(line);
		if (!*line){
			continue;
		}

		if (is_label(line)) {
			extract_label(line, label);
			
			if(!isalpha(label[0])){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			}

			if (symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
			strcpy(line, label);
			symtable_insert(label,instr_num);
			continue;

		}else if (is_Atype(line)) {
			if (!parse_A_instruction(line, &instr.a)){
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}
			instr.type = A_type;

			if(instr.a.is_addr){
				printf("A: %d\n", instr.a.address);
			}else{
				printf("A: %s\n", instr.a.label);
			}
			
		}else if (is_Ctype(line)) {

			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.c);

			if(instr.c.dest == DEST_INVALID){
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}

			if (instr.c.comp == COMP_INVALID) {
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}

			if (instr.c.jump == JMP_INVALID) {
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}

			instr.type = C_type; 
			printf("C: d=%d, c=%d, j=%d\n", instr.c.dest, instr.c.comp, instr.c.jump);
			
		}

	
		instructions[instr_num++] = instr;

		}

	return instr_num;

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

	size_t len = strlen(line);

	return (line[0] == '(' && line[len-1] == ')');
	
	// if ((line[0] == '(' && line[strlen(line) - 1] == ')')){
	// 	return true;
	// }
	// else{
	// 	return false;
	// }
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

void add_predefined_symbols(){
	for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){

		predefined_symbol symbol = predefined_symbols[i];
		symtable_insert(symbol.name, symbol.address);
	}
}

bool parse_A_instruction(const char *line, a_instruction *instr){
	char *s = malloc(strlen(line)); 
	strcpy(s, line + 1);
	char *s_end = NULL; 
	long result = strtol(s, &s_end, 10);

	if( s == s_end){
		
		instr->label = malloc(strlen(s));
		strcpy(instr->label, s);
		instr->is_addr = false; 
	
	} else if (*s_end != 0){
		
		return false;

	}else{
		instr->address = result;
		instr->is_addr = true; 
	}

	free(s);
	return true; 
}

void parse_C_instruction(char *line, c_instruction *instr){

	// split a temp value and a jump 
	char *temp = strtok(line, ";");
	char *jump = strtok(NULL, ";");

	//split to dest and comp
	char *dest = strtok(temp, "=");
	char *comp = strtok(NULL, "=");

	//catch if comp variable is NULL, meaing it is actually the destination 
	if (comp == NULL){
		comp = dest;
		dest = NULL;
	}

	int a = 0;
	instr->jump = str_to_jumpid(jump);
	instr->dest = str_to_destid(dest);
	instr->comp = str_to_compid(comp, &a);
	instr->a = a; 
	

}
