%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _TOKEN {
    eof = -1, identificador = 0, invalido = 1
} TOKEN;

%}

COM1 [^\n]*
COM2 [^*/]* 
PROT (if)|(else)|(while)|var|const|return|fn|=|bool|int|float|true|false|[(]|[)]|[{]|[}]|[;]|[:]
ID  [a-zA-z]+ 
LI  ([1-9][0-9]+)|([0])   
LF  (([1-9][0-9]+)|([0]))[\.][0-9]+
OB  [+]|[*]|==

%%
"//"{COM1}   {printf("%s é um Comentario\n", yytext);}
"/*"{COM2}"*/"  {printf("%s é um Comentario\n", yytext);}
{PROT}  {printf("%s é uma Palavra Reservada\n", yytext);}
{ID}    {printf("%s é um Identificador\n", yytext);}
{LI}    {printf("%s é um Literais inteiros\n", yytext);}
{LF}    {printf("%s é um Literais Floats\n", yytext);}
{OB}    {printf("%s é um Operadores Binarios\n", yytext);}      
['end'] { return -1; }

%%

/*Function yywrap is called by lex when input is exhausted.
Return 1 if you are done or 0 if more processing is required.*/
int yywrap(){
    return 1; 
}

int main()
{
    char fname[100];
    printf("\nEnter the name of file\n");
    scanf("%s",fname);
    yyin = fopen(fname,"r+");
    yylex();
    return 0;
}