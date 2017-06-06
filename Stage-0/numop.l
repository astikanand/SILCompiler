%{

#include<stdio.h>
#include<stdlib.h>

%}

number  [0-9]+
op      [-|+|*|/|^|=]

%%

   
{number} {printf("Number");}
{op}     {printf("Operator");}

%%


int yywrap(){
    return 1;
}


int main(){
    yylex();
    return 1;
}