%{
    #include <stdio.h>
    #include <stdlib.h>
    int yyerror();

    #define char* YYSTYPE;
%}

%token CHAR NEWLINE
 
%%

start : expr NEWLINE        { 
                                printf("\nComplete\n");
                                exit(1);
                            }
    ;

expr:  expr '+' expr        {   printf("+ ");        }
    | expr '-' expr         {   printf("- ");        }
    | expr '*' expr         {   printf("* ");        }
    | expr '/' expr         {   printf("/ ");        }
    | '(' expr ')'
    | CHAR                 {   printf("%c ",$1);    }
    ;

%%

void yyerror(char const *s){ 

    printf("yyerror  %s\n",s); 
    return ;
} 

int main(){

  yyparse();
  return 1;
}