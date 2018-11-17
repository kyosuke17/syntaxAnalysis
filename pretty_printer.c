#include <token_list.h>

#define NOMAL 0
#define ERROR 1

int break_flag;
int error(char message);

int block();
int var_dec();
int varname_array();
int var_name();
int type();
int standard_type();
int array_type();
int sub_program_dec();
int procedure_name();
int parameter();
int compound_st();
int statement();
int switch_st();
int while_st();
int break_st();
int procedure_call();
int formula_arrray();
int return_st();
int substitution_st();
int left_side();
int variable();
int fomula();
int simple_fomula();
int section();
int factor();
int constant();
int multi_ope();
int add_ope();
int relation_ope();
int input_st();
int output_st();
int output_specification();

void pretty_printer();

int parse_program() {
    if(token != TPROGRAM) {
        return error("Keyword 'program' is not found.");
    }
    token = scan();
    if(token != TNAME) {
        return error("Program name is not found.");
    }
    token = scan();
    if(token != TSEMI) {
        return error("; is not found.");
    }
    token = scan();
    if(block() == ERROR) {
        return ERROR;
    }
    if(token != TDOT) {
        return error("period is not found at the end");
    }
    token = scan();
    return NOMAL;
}

int block() {
    while(token == TVAR || tokne == TPROCEDURE) {
        if(token == TVAR) {
            if(var_dec() == ERROR) {
                return ERROR;
            }
        } else {
            if(sub_program_dec() == ERROR) {
                return ERROR;
            }
        }
    }
    if(compound_st() == ERROR) {
        return ERROR;
    }
    return NOMAL;
}

int ver_dec() {
    if(token != TVAR) {
        return error("Keyword 'var' is not found.");
    }
    token = scan();
    if(varname_array() == ERROR) {
        return ERROR;
    }
    if(token != TCOLON) {
        return error("colon is not found.");
    }
    token = scan();
    if(type() == ERROR) {
        return ERROR;
    }
    if(token != TSEMI) {
        return error("':' is not found.");
    }
    token = scan();
    while(token == TNAME) {
        if(varname_array() == ERROR) {
            return ERROR;
        }
        if(token != TCOLON) {
            return error("':' is not found.");
        }
        token = scan();
        if(type() == ERROR) {
            return ERROR;
        }
        if(token != TSEMI) {
            return error("';' is not found.");
        }
        token = scan();
    }
    return NOMAL;
}

int varname_array() {
    if(var_name() == ERROR) {
        return ERROR;
    }
    while(token == TCOMMA){
        if(token != TCOMMA) {
            return error("';' is not found");
        }
        token = scan();
        if(var_name() == ERROR) {
            return ERROR;
        }
    }
    return NOMAL;
}

int var_name() {
    if(token != TNAME) {
        return error("variable name is not found.");
    }
    token = scan();
    return NOMAL;
}

int type() {
    if(token == TINTEGER || token == TBOOLEAN || token == TCHAR) {
        if(standard_type() == ERROR) {
            return ERROR;
        }
    } else if (token == TARRAY) {
        if(array_type() == ERROR) {
            return ERROR;
        }
    } else {
        return error("type is not found.");
    }
    return NOMAL;
}

int standard_type() {
    if(token == TINTEGER || token == TBOOLEAN || token TCHAR ) {
        token = scan();
        return NOMAL;
    } else {
        return error("standard type is not found.");
    }
}

int array_type() {
    if(token != TVARRAY) {
        return error("keyboard 'array' is not found.");
    }
    token = scan();
    if(token != TLSQPAREN) {
        return error("'[' is not found.");
    }
    token = scan();
    if(token != TNUMBER) {
        return error("unsigned integer is not found.");
    }
    token = scan();
    if(token != EOF) {
        return error("keyword 'of' is not found.");
    }
    token = scan();
    if(standard_type() == ERROR) {
        return ERROR;
    }
    return NOMAL;
}

int sub_program_dec() {
    if(token != TPROCEDURE) {
        return error("keyword 'procedure' is not found.");
    }
    token = scan();
    if(procedure_name() == ERROR){
        return ERROR;
    }
    if(token == TLPAREN) {
        if(parameter() == ERROR) {
            return ERROR;
        }
    }
    if(token != TSEMI) {
        return error("';' is not found.");
    }
    token = scan();
    if(token == TVAR) {
        if(var_dec() == ERROR) {
            return ERROR;
        }
    }
    if(compound_st() == ERROR) {
        return ERROR;
    }
    if(token != TSEMI) {
        return error("';' is not found.");
    }
    token = scan();
    if(token == TVAR) {
        if(var_dec() == ERROR){
            return ERROR;
        }
    }
    if(compound_st() == ERROR) {
        return ERROR;
    }
    if(token != TSEMI) {
        return error("';' is not found.");
    }
    token = scan();
    return NOMAL;
}


int procedure_name() {
    if(token != TNAME) {
        return error("procedure name is not found.");
    }
    token = scan();
    return NOMAL;
}

int parameter() {
    if(token != TLPAREN) {
        return error("'(' is not found.");
    }
    token = scan();
    if(varname_array() == ERROR) {
        return ERROR;
    }
    if(token != TCOLON) {
        return error("Colon is not found.");
    }
    token = scan();
    if(type() == ERROR) {
        return ERROR;
    }
    while(token == TSEMI) {
        token = scan();
        if(varname_array() == ERROR) {
            return ERROR;
        }
        if(token != TCOLON) {
            return error("colon is not found.");
        }
        token = scan();
        if(type() == ERROR){
            return ERROR;
        }
    }
    if(token != TRPAREN) {
        return error("')' is not found.");
    }
    token = scan();
    return NOMAL;

}

int compound_st() {
    if(token != TBEGIN) {
		return error("Keyword 'begin' is not found.");
	}
	token = scan();
	if(statement() == ERROR){
		return ERROR;
	}
	while(token == TSEMI) {
		token = scan();
		if(statement() == ERROR){
			return ERROR;
		}
	}
	if(token != TEND) {
		return error("Keyword 'end' is not found.");
	}
	token = scan();
	return NORMAL;
}

int statement() {
	switch(token){
	case TNAME:
		if(substitution_st() == ERROR) {
			return ERROR;
		}
		break;
	case TIF:
		if(switch_st() == ERROR) {
			return ERROR;
		}
		break;
	case TWHILE:
		if(while_st() == ERROR) {
			return ERROR;
		}
		break;
	case TBREAK:
		if(break_st() == ERROR) {
			return ERROR;
		}
		break;
	case TCALL:
		if(procedure_call() == ERROR) {
			return ERROR;
		}
		break;
	case TRETURN:
		if(return_st() == ERROR) {
			return ERROR;
		}
		break;
	case TREAD:/* to do: */
	case TREADLN:
		if(input_st() == ERROR) {
			return ERROR;
		}
		break;
	case TWRITE:
	case TWRITELN:
		if(output_st() == ERROR) {
			return ERROR;
		}
		break;
	case TBEGIN:
		if(compound_st() == ERROR) {
			return ERROR;
		}
		break;
	}
	return NORMAL;
}

int switch_st() {
	if(token != TIF) {
		return error("Keyword 'if' is not found.");
	}
	token = scan();
	if(fomula() == ERROR) {
		return ERROR;
	}
	if(token != TTHEN) {
		return error("Keyword 'then' is not found.");
	}
	token =scan();
	if(statement() == ERROR) {
		return ERROR;
	}
	if(token == TELSE) {
		token = scan();
		if(statement() == ERROR) {
			return ERROR;
		}
	}
	return NORMAL;
}

int while_st() {
	b_flg = 1;
	if(token != TWHILE){
		return error("Keyword 'while' is not found.");
	}
	token = scan();
	if(fomula() == ERROR){
		return ERROR;
	}
	if(token != TDO){
		return error("Keyword 'do' is not found.");
	}
	token = scan();
	if(statement() == ERROR){
		return ERROR;
	}
	b_flg = 0;
	return NORMAL;
}

int break_st() {
    if(!b_flg){
		return error("Keyword 'break' is found  outside the while statement.");
	}
	if(token != TBREAK){
		return error("Keyword 'break' is not found.");
	}
	return NORMAL;
}

int procedure_call() {
    if(token != TCALL){
		return error("Keyword 'call' is not found.");
	}
	token = scan();
	if(procedure_name() == ERROR){
		return ERROR;
	}
	if(token == TLPAREN){
		token =scan();
		if(formula_array() == ERROR){
			return ERROR;
		}
		if(token != TRPAREN){
			return error("')' is not found.");
		}
		token = scan();
	}
	return NORMAL;
}

int formula_array() {
    if(fomula() == ERROR) {
        return ERROR;
    }
    while(token == TCOMMA) {
        token = scan();
        if(fomula() == ERROR) {
            return ERROR;
        }
    }
    return ERROR;
}

int return_st() {
    if(token != TRETURN) {
        return error("keyword 'return' is not found.");
    }
    token = scan();
    return NOMAL;
}

int substitution_st() {
    if(left_side() == ERROR) {
        return ERROR;
    }
    if(token != TASSIGN) {
        return error("':=' is not found.");
    }
    token = scan();
    if(fomula() == ERROR){
        return ERROR;
    }
    return NORMAL;
}

int left_side() {
    if(variable() == ERROR) {
        return ERROR;
    }
    return NOMAL;
}

int variable() {
    if(var_name() == ERROR) {
        return ERROR;
    }
    if(token == TLSQPAREN) {
        token = scan();
        if(fomula() == ERROR) {
            return ERROR;
        }
        if(token != TRSQPAREN) {
            return error("']' is not found.");
        }
        token = scan();
    }
    return NORMAL;
}

int fomula() {
	if(simple_fomula() == ERROR){
		return ERROR;
	}
	while(token == TEQUAL||token == TNOTEQ||token == TLE||token == TLEEQ||token == TGR||token == TGREQ){
		if(relational_ope() == ERROR){
			return ERROR;
		}
		if(simple_fomula() == ERROR){
			return ERROR;
		}
	}
	return NORMAL;
}

int simple_fomula(){
	if(token == TPLUS||token == TMINUS){
		token = scan();
	}
	if(section() == ERROR){
		return ERROR;
	}
	while(token == TPLUS||token == TMINUS||token == TOR){
		if(add_ope() == ERROR){
			return ERROR;
		}
		if(section() == ERROR){
			return ERROR;
		}
	}
	return NORMAL;
}

int section() {
	if(factor()==ERROR){
		return ERROR;
	}
	while(token == TSTAR||token == TAND||token == TDIV){
		if(multi_ope() == ERROR){
			return ERROR;
		}
		if(factor() == ERROR){
			return ERROR;
		}
	}
	return NORMAL;
}

int factor() {
	switch(token){
	case TNAME:
		if(variable() == ERROR){
			return ERROR;
		}
		break;
	case TNUMBER:
		if(constant() == ERROR){
			return ERROR;
		}
		break;
	case TLPAREN:
		token = scan();
		if(fomula() == ERROR){
			return ERROR;
		}
		if(token != TRPAREN){
			return error("')' is not found.");
		}
		token = scan();
		break;
	case TNOT:
		token = scan();
		if(factor() == ERROR){
			return ERROR;
		}
		break;
	case TINTEGER:
	case TBOOLEAN:
	case TCHAR:
		if(standard_type() == ERROR){
			return ERROR;
		}
		if(token != TLPAREN){
			return error("'(' is not found.");
		}
		token = scan();
		if(fomula() == ERROR){
			return ERROR;
		}
		if(token != TRPAREN){
			return error("')' is not found.");
		}
		break;
	default:
		token = scan();
	}
	return NORMAL;
}

int constant() {
	if(token != TNUMBER&&token != TFALSE&&token != TTRUE&&token != TSTRING){
		return error("Constant is not found.");
	}
	token = scan();
	return NORMAL;
}

int multi_ope() {
	if(token != TSTAR&&token != TDIV&&token != TAND){
		return error("Multiplicative operator is not found.");
	}
	token = scan();
	return NORMAL;
}

int add_ope() {
	if(token != TMINUS&&token != TPLUS&&token != TOR){
		return error("Additive operator is not found.");
	}
	token = scan();
	return NORMAL;
}

int relational_ope() {
	if(token != TEQUAL&&token != TNOTEQ&&token != TLE&&token != TLEEQ&&token != TGR&&token != TGREQ){
		return error("relational operator is not found.");
	}
	token = scan();
	return NORMAL;
}

int input_st() {
	if(token != TREAD&&token != TREADLN){
		return error("Keyword 'read' or 'readln' is not found.");
	}
	token = scan();
	if(token == TLPAREN){
		token = scan();
		if(variable() == ERROR){
			return ERROR;
		}
		while(token == TCOMMA){
			token = scan();
			if(variable() == ERROR){
				return ERROR;
			}
		}
		if(token != TRPAREN){
			return error("')' is not found.");
		}
		token = scan();
	}
	return NORMAL;
}

int output_st() {
	if(token != TWRITE&&token != TWRITELN){
		return error("Keyword 'write' or 'writeln' is not found.");
	}
	token = scan();
	if(token == TLPAREN){
		token = scan();
		if(output_specification() == ERROR){
			return ERROR;
		}

		while(token == TCOMMA){
			token = scan();
			if(output_specification() == ERROR){
				return ERROR;
			}
		}
		if(token != TRPAREN){
			return error("')' is not found.");
		}
		token = scan();
	}
	return NORMAL;
}

int output_specification() {
	if((token == '+')||(token == '-')||(token == TNAME)||(token == TNUMBER)||(token == TLPAREN)||(token == TNOT)||(token == TINTEGER)||(token == TBOOLEAN)||(token == TCHAR)){
		if(fomula() == ERROR){
			return ERROR;
		}
		if(token == TCOLON){
			token = scan();
			if(token != TNUMBER){
				return error("Unsigned integer is not found.");
			}
			token = scan();
		}
	}
	else if(token == TSTRING){
		token = scan();
	}
	return NORMAL;
}

int error(char *message) {
    printf('\nERROR : %s  \n at line %d\n',message,get_linenum());
    end_scan();
    return ERROR;
}

void pretty_printer() {
    int start_st;


    int sub_dec = 0;
    int n_line = 0;
    int count = 0;

    while((token = scan()) >= 0) {
        if(token != TBEGIN && sub_dec && n_line) {
            printf("    ");
        }
        n_line = 0;
        switch(token) {
            case TPROGRAM:
                printf("%s ",tokenstr[token]);
                start_st = get_linenum();
                break;
            case TPROCEDURE:
                sub_dec = 1;
            case TVAR:
                if(get_linenum() == start_st + 1) {
                    printf("    ");
                }
                printf("%s ", tokenstr[token]);
                break;
            case TBEGIN:
                ++cnt;
                n_line = 1;
                printf("%s \n", tokenstr[token]);
                for(int i = 0; i < cnt; i++) {
                    printf("    ");
                }
                break;
            case TSEMI:
                printf(";\n");
                n_line = 1;
                for(int i = 0;i < count; i++) {
                    printf("    ");
                }
                break;
            case TNAME:
                printf("%s ", string_attr);
                break;
            case TSTRING:
                printf("'%s'", string_attr);
                break;
            case TNUMBER:
                printf("%d ", num_attr);
                break;
            case TLPAREN:
                printf("%s", tokenstr[token]);
                break;
            case TELSE:
                printf("%s\n    ", tokenstr[token]);
                break;
            case TEND:
                --count;
                printf("\n");
                for(int i = 0;i < count;i++) {
                    printf("    ");
                }
                printf("%s", tokenstr[token]);
                break;
            default:
                printf("%s ", tokenstr[token]);
        }
    }
}