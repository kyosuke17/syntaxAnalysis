/*
 ============================================================================
 Name        : kadai01.c
 Author      : Kyosuke Yokota
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "token_list.h"

/* keyword list */
struct KEY key[KEYWORDSIZE] = {
	{"and", 	TAND	},
	{"array",	TARRAY	},
	{"begin",	TBEGIN	},
	{"boolean",	TBOOLEAN},
	{"break",	TBREAK  },
	{"call",	TCALL	},
	{"char",	TCHAR	},
	{"div",		TDIV	},
	{"do",		TDO	},
	{"else",	TELSE	},
	{"end",		TEND	},
	{"false",	TFALSE	},
	{"if",		TIF	},
	{"integer",	TINTEGER},
	{"not",		TNOT	},
	{"of",		TOF	},
	{"or",		TOR	},
	{"procedure", TPROCEDURE},
	{"program",	TPROGRAM},
	{"read",	TREAD	},
	{"readln",	TREADLN },
	{"return", 	TRETURN },
	{"then",	TTHEN	},
	{"true",	TTRUE	},
	{"var",		TVAR	},
	{"while",	TWHILE	},
	{"write",	TWRITE  },
	{"writeln",	TWRITELN}
};

/* Token counter */
int numtoken[NUMOFTOKEN+1];

/* string of each token */
char *tokenstr[NUMOFTOKEN+1] = {
	"",
	"NAME", "program", "var", "array", "of", "begin", "end", "if", "then",
	 "else", "procedure", "return", "call", "while", "do", "not", "or",
	"div", "and", "char", "integer", "boolean", "readln", "writeln", "true",
	 "false", "NUMBER", "STRING", "+", "-", "*", "=", "<>", "<", "<=", ">",
	">=", "(", ")", "[", "]", ":=", ".", ",", ":", ";", "read","write", "break"
};
int main(int nc, char *np[]) {
	int token, i;
	token = 0;

	if(nc < 2) {
		printf("File name id not given.\n");
		return 0;
	}
	if(init_scan(np[1]) < 0) {
		printf("File %s can not open.\n", np[1]);
		return 0;
	}
	token = scan();
	if(parse_program() == NORMAL) {
		end_scan();
		/* pretty printer */
		init_scan(np(1));
		pretty_printer();
	}
	return 0;
}


void error(char *mes) {
	printf("\n ERROR: %s\n", mes);
	end_scan();
}
