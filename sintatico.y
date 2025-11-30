%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines para evitar erro de INT/LOG */
#ifndef INT
#define INT 0
#endif
#ifndef LOG
#define LOG 1
#endif

/* --- DEFINIÇÃO DA ESTRUCTURA AQUI (Para evitar conflitos) --- */
typedef struct {
    char id[100];
    int end;
    int tip;
} elemTabSimb;
/* ------------------------------------------------------------ */

/* INCLUI OS ARQUIVOS QUE USAM ESSA STRUCT */
#include "utils.c"
#include "tree.c"

int yylex();
void yyerror(char *);

extern char NomePrograma[100];

ptno Raiz;
%}

%union {
    int valor;
    char ident[100];
    ptno no;
}

%token T_PROGRAMA T_INICIO T_FIM T_INTEIRO
%token T_LEIA T_ESCREVA T_ATRIB T_ABRE T_FECHA
%token T_MAIS T_MENOS T_MULT T_DIV
%token T_SE T_ENTAO T_SENAO T_FIMSE
%token T_ENQTO T_FACA T_FIMENQTO
%token T_MAIOR T_MENOR T_IGUAL
%token T_NAO

%token <valor> T_NUM
%token <ident> T_IDENTIF

%type <no> programa declaracao lista_vars comando lista_comandos expr

%left T_MAIOR T_MENOR T_IGUAL
%left T_MAIS T_MENOS
%left T_MULT T_DIV
%left T_NAO

%start programa

%%

programa: T_PROGRAMA T_IDENTIF declaracao T_INICIO lista_comandos T_FIM
    {
        strcpy(NomePrograma, $2); 
        Raiz = criaNo(NO_PROGRAMA, 0);
        ptno id = criaNo(NO_ID_PROGRAMA, 0); 
        
        adicionaFilho(Raiz, $5); 
        adicionaFilho(Raiz, $3); 
        adicionaFilho(Raiz, id); 
        
        geraDot(Raiz);
        
        printf("\tINPP\n");
        printf("\tAMEM %d\n", topoTab);
        geracod(Raiz);
        printf("\tDMEM %d\n", topoTab);
        printf("\tFIMP\n");
    }
    ;

declaracao: T_INTEIRO lista_vars 
          { 
             $$ = criaNo(NO_DECLARACAO, 0);
             ptno tipo = criaNo(NO_TIPO_INTEIRO, 0);
             adicionaFilho($$, $2);   
             adicionaFilho($$, tipo); 
          }
          | /* vazio */ { $$ = NULL; }
          ;

lista_vars: T_IDENTIF 
          { 
             elemTabSimb elem; strcpy(elem.id, $1); elem.end = topoTab; elem.tip = INT;
             insereSimbolo(elem);
             
             $$ = criaNo(NO_LISTA_VARS, 0);
             ptno id = criaNo(NO_IDENTIFICADOR, topoTab-1); 
             adicionaFilho($$, id);
          }
          | T_IDENTIF lista_vars
          {
             elemTabSimb elem; strcpy(elem.id, $1); elem.end = topoTab; elem.tip = INT;
             insereSimbolo(elem);
             
             $$ = criaNo(NO_LISTA_VARS, 0);
             ptno id = criaNo(NO_IDENTIFICADOR, topoTab-1);
             adicionaFilho($$, $2); 
             adicionaFilho($$, id);
          }
          ;

lista_comandos: comando 
              { 
                 $$ = criaNo(NO_LISTA_CMDS, 0);
                 adicionaFilho($$, $1);
              }
              | comando lista_comandos
              { 
                 $$ = criaNo(NO_LISTA_CMDS, 0);
                 adicionaFilho($$, $2); 
                 adicionaFilho($$, $1); 
              }
              ;

comando: T_LEIA T_IDENTIF
       { 
         int pos = buscaSimbolo($2);
         $$ = criaNo(NO_LEITURA, 0);
         ptno id = criaNo(NO_IDENTIFICADOR, pos);
         adicionaFilho($$, id);
       }
       | T_ESCREVA expr
       {
         $$ = criaNo(NO_ESCRITA, 0);
         adicionaFilho($$, $2);
       }
       | T_IDENTIF T_ATRIB expr
       {
         int pos = buscaSimbolo($1);
         $$ = criaNo(NO_ATRIBUICAO, 0);
         
         /* --- CORREÇÃO VISUAL AQUI --- */
         /* Antes estava NO_VARIAVEL, mudamos para NO_IDENTIFICADOR para igualar ao PDF */
         ptno id = criaNo(NO_IDENTIFICADOR, pos);
         
         /* Ordem de inserção: Ultimo entra primeiro na lista (Esq) */
         adicionaFilho($$, $3);   // Expr (Direita)
         adicionaFilho($$, id);   // Identificador (Esquerda)
       }
       | T_SE expr T_ENTAO lista_comandos T_FIMSE
       {
         $$ = criaNo(NO_SELECAO, 0);
         adicionaFilho($$, $4); 
         adicionaFilho($$, $2); 
       }
       | T_SE expr T_ENTAO lista_comandos T_SENAO lista_comandos T_FIMSE
       {
         $$ = criaNo(NO_SELECAO, 0);
         adicionaFilho($$, $6); 
         adicionaFilho($$, $4); 
         adicionaFilho($$, $2); 
       }
       | T_ENQTO expr T_FACA lista_comandos T_FIMENQTO
       {
         $$ = criaNo(NO_REPETICAO, 0);
         adicionaFilho($$, $4);
         adicionaFilho($$, $2);
       }
       ;

expr: expr T_MAIS expr   { $$ = criaNo(NO_SOMA, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | expr T_MENOS expr  { $$ = criaNo(NO_SUB, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | expr T_MULT expr   { $$ = criaNo(NO_MULT, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | expr T_DIV expr    { $$ = criaNo(NO_DIV, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | expr T_MAIOR expr  { $$ = criaNo(NO_MAIOR, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | expr T_MENOR expr  { $$ = criaNo(NO_MENOR, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | expr T_IGUAL expr  { $$ = criaNo(NO_IGUAL, 0); adicionaFilho($$, $3); adicionaFilho($$, $1); }
    | T_NAO expr         { $$ = criaNo(NO_NEGACAO, 0); adicionaFilho($$, $2); }
    | T_ABRE expr T_FECHA { $$ = $2; }
    | T_NUM              { $$ = criaNo(NO_NUMERO, $1); }
    | T_IDENTIF          
    { 
       int pos = buscaSimbolo($1);
       $$ = criaNo(NO_VARIAVEL, pos); 
    }
    ;

%%

void yyerror (char *msg) { printf("Erro: %s\n", msg); }
int main() { yyparse(); return 0; }