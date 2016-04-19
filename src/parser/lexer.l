%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string> // this is literally only here so that the compiler knows what `std::` is

#include "nodes/all.h"
#include "parser/NodeVector.h"
#include "parser/parser.h"
#include "parser/fix.h"

using namespace prolog::nodes;

int line_number = 1;

%}

%option reentrant bison-bridge noyywrap yylineno

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
    yylval->string_val = strdup(yytext);
	return STRING_CONST;
}

[A-Za-z][A-Za-z0-9]* {
	yylval->string_val = strdup(yytext);
	return LITERAL;
}
