%{

#include <stdio.h> 
int num1;
int num2;
 
%}
 
number [0-9]*
 
%%
 
{number}[0|2|4|6|8] {
	printf("Even number [%d]",yyleng);
	return atoi(yytext);
}
 
{number}[1|3|5|7|9] {
    printf("Odd number [%d]",yyleng);
    return atoi(yytext);
}
%%
 
int yywrap(){
    return 1;
}
 
int main(){

    printf("Input an even number and an odd number\n");
    num1 = yylex();
    num2 = yylex();
    int diff = num1 - num2;

    if(diff % 2 != 0)
        printf("\nYour inputs were checked for correctness, \nResult : Correct\n");
    else
        printf("\nYour inputs were checked for correctness, \nResult : Incorrect\n");
    return 1;
}