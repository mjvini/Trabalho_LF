%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *out ;

typedef enum _TOKEN {
    eof = -1, identificador = 0, invalido = 1
} TOKEN;

int n_linhas = 1; //contador de linhas
int n_coluna = 1; //contador de colunas

%}

NL \n
RESTO .

COM1 [^\n]*
COM2 [^*/]* 
PROT (if)|(else)|(while)|var|const|return|fn|=|bool|int|float|true|false|[(]|[)]|[{]|[}]|[;]|[:]
ID  [a-zA-z]+ 
LI  ([1-9][0-9]*)|([0])   
LF  (([1-9][0-9]+)|([0]))[\.][0-9]+
OB  [+]|[*]|==
INVALIDO [.*]|([0][0]+[0-9]+[\.][0-9]+)|([0]+)|([\.][0-9]*)

%%
    //Regras:

{INVALIDO}    {fprintf(out,"(Invalido,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
"//"{COM1}   {fprintf(out,"(Comentario,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
"/*"{COM2}"*/"  {fprintf(out,"(Comentario,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
{PROT}  {fprintf(out,"(Palavra Reservada,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
{ID}    {fprintf(out,"(Identificador,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
{LI}   	{fprintf(out,"(Literal Inteiro,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
{LF}    {fprintf(out,"(Literal float,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);}
{OB}    {fprintf(out,"(Operador Binario,\"%s\",%d,%d)\n",yytext,n_linhas, n_coluna);} 
{NL} {n_linhas++, n_coluna = 1;}
{RESTO} {n_coluna++;}

%%

/*Function yywrap is called by lex when input is exhausted.
Return 1 if you are done or 0 if more processing is required.*/
int yywrap(){
    return 1; 
}

int main(int argc, char *argv[]){

    FILE *arquivo = fopen(argv[1],"r");
    yyin = arquivo;
    
    out = fopen(argv[2],"w");
    yylex();
    return 0;
}
