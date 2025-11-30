#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TAB 100
#define TAM_PIL 100

/* Variável Global para o nome do programa */
char NomePrograma[100] = "";

/* A struct elemTabSimb agora é definida no sintatico.y antes de incluir este arquivo */

elemTabSimb tabSimb[TAM_TAB];
int topoTab = 0;

void yyerror(char *s);

void insereSimbolo(elemTabSimb elem) {
    int i;
    if (topoTab == TAM_TAB) {
        yyerror("Erro: Tabela de simbolos cheia\n");
        exit(1);
    }
    for (i = topoTab - 1; i >= 0 && strcmp(tabSimb[i].id, elem.id) != 0; i--);
    if (i != -1) {
        char msg[200];
        sprintf(msg, "Erro: simbolo %s ja declarado", elem.id);
        yyerror(msg);
        exit(1);
    }
    tabSimb[topoTab++] = elem;
}

int buscaSimbolo(char *id) {
    int i;
    for (i = topoTab - 1; i >= 0 && strcmp(tabSimb[i].id, id) != 0; i--);
    if (i == -1) {
        char msg[200];
        sprintf(msg, "Erro: simbolo %s nao declarado", id);
        yyerror(msg);
        exit(1);
    }
    return i;
}

int Pilha[TAM_PIL];
int topo = -1;

void empilha(int valor) {
    if (topo == TAM_PIL - 1) { yyerror("Erro: Pilha cheia\n"); exit(1); }
    Pilha[++topo] = valor;
}

int desempilha(void) {
    if (topo == -1) { yyerror("Erro: Pilha vazia\n"); exit(1); }
    return Pilha[topo--];
}