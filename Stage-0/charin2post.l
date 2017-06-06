%{
	#include <stdlib.h>
    #include <stdio.h> 
	#include "y.tab.h"
%}

%%

[a-z]+	{
            yylval = *yytext;
            return CHAR;
        }
"+"	        return *yytext;
"-"	        return *yytext;
"*"	        return *yytext;
"/"	        return *yytext;
[()]	    return *yytext;
[\n]        return NEWLINE;

%%

int yywrap(){
	return 1;
}