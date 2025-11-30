/*
+-------------------------------------------------------------+
| UNIFAL - Universidade Federal de Alfenas.                   |
| BACHARELADO EM CIENCIA DA COMPUTACAO.                       |
| Trabalho: Construcao Arvore Sintatica e Geracao de Codigo   |
| Disciplina: Teoria de Linguagens e Compiladores             |
| Professor: Luiz Eduardo da Silva                            |
| Aluno: Bárbara Silveira Rodrigues                           |
| Data: 30/11/2025                                            |
+-------------------------------------------------------------+
*/


%{
#include <stdlib.h>
#include <string.h>
typedef struct no *ptno;
#include "sintatico.h" 



void yyerror(char *);
%}

%%

"programa"    { return T_PROGRAMA; }
"inicio"      { return T_INICIO; }
"fimprograma" { return T_FIM; }
"inteiro"     { return T_INTEIRO; }
"leia"        { return T_LEIA; }
"escreva"     { return T_ESCREVA; }
"se"          { return T_SE; }
"entao"       { return T_ENTAO; }
"senao"       { return T_SENAO; }     /* NOVO */
"fimse"       { return T_FIMSE; }
"enquanto"    { return T_ENQTO; }
"faca"        { return T_FACA; }
"fimenquanto" { return T_FIMENQTO; }

"nao"         { return T_NAO; }       /* NOVO */

"+"           { return T_MAIS; }
"-"           { return T_MENOS; }
"*"           { return T_MULT; }
"/"           { return T_DIV; }
">"           { return T_MAIOR; }
"<"           { return T_MENOR; }
"="           { return T_IGUAL; }

"<-"          { return T_ATRIB; }
"("           { return T_ABRE; }
")"           { return T_FECHA; }

[a-zA-Z][a-zA-Z0-9]* { 
    strcpy(yylval.ident, yytext); 
    return T_IDENTIF; 
}

[0-9]+        { 
    yylval.valor = atoi(yytext); 
    return T_NUM; 
}

[ \t\n]       ; 

.             { yyerror("Erro lexico"); }

%%

int yywrap(void) { return 1; }