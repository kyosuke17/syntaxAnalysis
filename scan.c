#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "token_list.h"

int num_attr;
int line_num;
char string_attr[MAXSTRSIZE];
int cbuf;
FILE *fp;
int eof = 0;

int init_scan(char *filename)
{
	if ((fp = fopen(filename, "r")) == NULL)
	{
		return -1;
	}
	line_num = 0;
	rewind(fp);
	if ((cbuf = getc(fp)) == EOF)
	{
		error("No data");
	}
	return 0;
}

int scan(void)
{

	char string[MAXSTRSIZE] = {};
	char *p = string;
	int i;

	if (eof == 1)
	{
		return EOF;
	}
	/*alpha*/
	if (isalpha(cbuf))
	{
		do
		{
			*p++ = cbuf;
			if ((cbuf = getc(fp)) == EOF)
			{
				eof = 1;
			}
		} while (isalnum(cbuf));
		if (!strcmp("writeln", string))
		{
			return TWRITELN;
		}
		else if (!strcmp("readln", string))
		{
			return TREADLN;
		}
		for (i = 0; i <= KEYWORDSIZE; i++)
		{
			if (!strncmp(key[i].keyword, string, (char)sizeof(key[i].keyword)))
			{
				return key[i].keytoken;
			}
		}
		strcpy(string_attr, string);
		return TNAME;
	}
	/*num*/
	else if (isdigit(cbuf))
	{

		do
		{
			*p++ = cbuf;

			if ((cbuf = getc(fp)) == EOF)
			{
				eof = 1;
			}
			else if (isalpha(cbuf))
			{
				return -1;
			}
		} while (isdigit(cbuf));

		if ((num_attr = atoi(string)) > 32767)
		{
			return -1;
		}
		return TNUMBER;
	}

	/*symbol*/
	switch (cbuf)
	{
	case '+':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TPLUS;
	case '-':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TMINUS;
	case '*':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TSTAR;
	case '=':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TEQUAL;
	case '<':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		switch (cbuf)
		{
		case '>':
			if ((cbuf = getc(fp)) == EOF)
			{
				eof = 1;
			}
			return TNOTEQ;
		case '=':
			if ((cbuf = getc(fp)) == EOF)
			{
				eof = 1;
			}
			return TLEEQ;
		}
		return TLE;
	case '>':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		else if (cbuf == '=')
		{
			if ((cbuf = getc(fp)) == EOF)
			{
				eof = 1;
			}
			return TGREQ;
		}
		return TGR;
	case '(':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TLPAREN;
	case ')':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TRPAREN;
	case '[':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TLSQPAREN;
	case ']':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TRSQPAREN;
	case '.':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TDOT;
	case ',':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TCOMMA;
	case ':':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		else if (cbuf == '=')
		{
			if ((cbuf = getc(fp)) == EOF)
			{
				eof = 1;
			}
			return TASSIGN;
		}
		return TCOLON;
	case ';':
		if ((cbuf = getc(fp)) == EOF)
		{
			eof = 1;
		}
		return TSEMI;
	case '/':
		if ((cbuf = getc(fp)) == EOF)
		{
			return EOF;
		}
		else if (cbuf == '*')
		{
			while (1)
			{
				if ((cbuf = getc(fp)) == EOF)
				{
					return EOF;
				}
				else if (cbuf == '*')
				{
					if ((cbuf = getc(fp)) == EOF)
					{
						return EOF;
					}
					else if (cbuf == '/')
					{
						if ((cbuf = getc(fp)) == EOF)
						{
							eof = 1;
						}
						return scan();
					}
				}
			}
			break;
		}
		return -1;
	case '{':
		while (1)
		{
			if ((cbuf = getc(fp)) == EOF)
			{
				return -1;
			}
			else if (cbuf == '}')
			{
				if ((cbuf = getc(fp)) == EOF)
				{
					eof = 1;
				}
				return scan();
			}
		}
		break;
	case '\'':
		while (1)
		{
			if ((cbuf = getc(fp)) == EOF)
			{
				return EOF;
			}
			else if (cbuf == '\'')
			{
				if ((cbuf = getc(fp)) == EOF)
				{
					eof = 1;
				}
				strcpy(string_attr, string);
				return TSTRING;
			}
			*p++ = cbuf;
		}
		break;
	case ' ':
		if ((cbuf = getc(fp)) == EOF)
		{
			return EOF;
		}
		return scan();
	case '\t':
		if ((cbuf = getc(fp)) == EOF)
		{
			return EOF;
		}
		return scan();
	case '\r':
		if ((cbuf = getc(fp)) == EOF)
		{
			return EOF;
		}
		else if (cbuf == '\n')
		{
			if ((cbuf = getc(fp)) == EOF)
			{
				return EOF;
			}
			line_num++;
			return scan();
		}
		line_num++;
		return scan();
	case '\n':
		if ((cbuf = getc(fp)) == EOF)
		{
			return EOF;
		}
		else if (cbuf == '\r')
		{
			if ((cbuf = getc(fp)) == EOF)
			{
				return EOF;
			}
			line_num++;
			return scan();
		}
		line_num++;
		return scan();
	}
	return -1;
}

int get_linenum(void)
{
	if (!cbuf)
	{
		return 0;
	}
	return line_num;
}

void end_scan(void)
{
	fclose(fp);
}
