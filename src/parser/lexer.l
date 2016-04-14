%option yylineno

%{
// this is in raw C because the C++ version of flex on OS X doesnt want to play ball

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
int line_number = 1;

extern "C" int yywrap() {
    return 1;
}

%}

%%

\n {
    line_number++;
}

[ \t\r]	{
	/* Discard newlines, spaces, and tabs */
}

"(" {
	return LPAREN;
}

")" {
	return RPAREN;
}

"," {
    return AND;
}

"." {
    return FULL_STOP;
}

\"[A-Za-z0-9]*\" {
    yylval.string_val = strdup(yytext);
	return STRING_CONST;
}

[A-Za-z][A-Za-z0-9]* {
	yylval.string_val = strdup(yytext);
	return LITERAL;
}
