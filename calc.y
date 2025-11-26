%{
#include <stdio.h>
#include "lexico.c"
#define YYSTYPE ptno
ptno Raiz;
%}

%token T_ENTER
%token T_MAIS
%token T_MENOS
%token T_MULT
%token T_DIV
%token T_ABRE
%token T_FECHA
%token T_NUM

%start calculo

%left T_MAIS T_MENOS
%left T_MULT T_DIV

%%

calculo: calculo expr T_ENTER 
            { 
                Raiz = $2;
                geraDot(Raiz);
                //mostra(Raiz, 0);

                printf("\n\tINPP\n"); // Cabeçalho obrigatório da MVS
                geracod(Raiz);        // Gera as instruções da conta
                printf("\tFIMP\n");   // Rodapé obrigatório da MVS

            }
       | 
       ;

expr : expr T_MAIS expr 
           { 
              ptno n = criaNo('+', 0);
              adicionaFilho(n, $3);
              adicionaFilho(n, $1);
              $$ = n;
           }
     | expr T_MENOS expr 
           { 
              ptno n = criaNo('-', 0);
              adicionaFilho(n, $3);
              adicionaFilho(n, $1);
              $$ = n;
           }
     | expr T_MULT expr 
           { 
              ptno n = criaNo('*', 0);
              adicionaFilho(n, $3);
              adicionaFilho(n, $1);
              $$ = n;
           }
     | expr T_DIV expr 
           { 
              ptno n = criaNo('/', 0);
              adicionaFilho(n, $3);
              adicionaFilho(n, $1);
              $$ = n;
           }
     | T_ABRE expr T_FECHA 
           { $$ = $2; }
     | T_NUM 
           { $$ = $1; }
     ;

%%

void yyerror (char *msg) {
    printf("Erro: %s\n", msg);
} 

int main() {
    yyparse();
    return 0;
}
