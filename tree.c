#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Enumeração dos Tipos de Nós */
enum {
    NO_PROGRAMA = 100, NO_DECLARACAO, NO_LISTA_VARS, NO_TIPO_INTEIRO, 
    NO_LISTA_CMDS, NO_BLOCO, 
    NO_LEITURA, NO_ESCRITA, NO_ATRIBUICAO, NO_SELECAO, NO_REPETICAO, NO_CONDICAO,
    NO_IDENTIFICADOR, NO_VARIAVEL, NO_NUMERO, NO_ID_PROGRAMA,
    NO_SOMA, NO_SUB, NO_MULT, NO_DIV,
    NO_MAIOR, NO_MENOR, NO_IGUAL, NO_NEGACAO
};

/* --- ACESSO AOS DADOS EXTERNOS --- */
/* struct elemTabSimb vem do sintatico.y (inclusão mestre) */
extern elemTabSimb tabSimb[]; 
extern char NomePrograma[];

typedef struct no *ptno;

struct no {
    int tipo;
    int valor;
    ptno filho;
    ptno irmao;
};

ptno criaNo(int tipo, int valor) {
    ptno n = (ptno)malloc(sizeof(struct no));
    n->tipo = tipo;
    n->valor = valor;
    n->filho = NULL;
    n->irmao = NULL;
    return n;
}

void adicionaFilho(ptno pai, ptno filho) {
    if (!pai || !filho) return;
    filho->irmao = pai->filho;
    pai->filho = filho;
}

char* nomeNo(int tipo) {
    switch(tipo) {
        case NO_PROGRAMA: return "programa";
        case NO_DECLARACAO: return "declaracao de variaveis";
        case NO_LISTA_VARS: return "lista variaveis";
        case NO_TIPO_INTEIRO: return "tipo inteiro";
        case NO_LISTA_CMDS: return "lista comandos";
        case NO_LEITURA: return "leitura";
        case NO_ESCRITA: return "escrita";
        case NO_ATRIBUICAO: return "atribuicao";
        case NO_SELECAO: return "selecao";
        case NO_REPETICAO: return "repeticao";
        case NO_CONDICAO: return "condicao";
        
        case NO_IDENTIFICADOR: return "identificador";
        case NO_ID_PROGRAMA: return "identificador";
        case NO_VARIAVEL: return "variavel";
        case NO_NUMERO: return "numero";
        
        case NO_SOMA: return "soma"; 
        case NO_SUB: return "subtrai";
        case NO_MULT: return "multiplica";
        case NO_DIV: return "divide";
        case NO_MAIOR: return "compara maior";
        case NO_MENOR: return "compara menor";
        case NO_IGUAL: return "compara igual";
        case NO_NEGACAO: return "negacao (NAO)";
        default: return "node";
    }
}

int Etiqueta = 1;

/* GERAÇÃO DE CÓDIGO */
void geracod(ptno Raiz) {
    if (!Raiz) return;

    if (Raiz->tipo == NO_PROGRAMA || Raiz->tipo == NO_DECLARACAO || 
        Raiz->tipo == NO_LISTA_VARS || Raiz->tipo == NO_TIPO_INTEIRO ||
        Raiz->tipo == NO_BLOCO || Raiz->tipo == NO_LISTA_CMDS || 
        Raiz->tipo == NO_CONDICAO) {
        
        ptno p = Raiz->filho;
        while(p) {
            geracod(p);
            p = p->irmao;
        }
        return;
    }

    if (Raiz->tipo == NO_LEITURA) {
        printf("\tLEIT\n");
        printf("\tARMZ %d\n", Raiz->filho->valor);
        return;
    }

    if (Raiz->tipo == NO_ESCRITA) {
        geracod(Raiz->filho); 
        printf("\tIMPR\n");
        return;
    }

    if (Raiz->tipo == NO_ATRIBUICAO) {
        // Agora: Filho 1 (Esq) = Var, Filho 2 (Dir) = Expr
        ptno var = Raiz->filho;
        ptno expr = var->irmao;
        geracod(expr);
        printf("\tARMZ %d\n", var->valor);
        return;
    }

    if (Raiz->tipo == NO_SELECAO) {
        ptno p = Raiz->filho;
        ptno cond = NULL, bTrue = NULL, bFalse = NULL;

        if (p->irmao && p->irmao->irmao) {
            cond = p->irmao->irmao;
            bTrue = p->irmao;
            bFalse = p;
        } else {
            cond = p->irmao;
            bTrue = p;
        }

        int L_Else = Etiqueta++;
        int L_Fim = Etiqueta++;

        geracod(cond);
        printf("\tDSVF L%d\n", L_Else);
        geracod(bTrue);
        
        if (bFalse) {
            printf("\tDSVS L%d\n", L_Fim);
            printf("L%d\tNADA\n", L_Else);
            geracod(bFalse);
            printf("L%d\tNADA\n", L_Fim);
        } else {
            printf("L%d\tNADA\n", L_Else);
        }
        return;
    }

    if (Raiz->tipo == NO_REPETICAO) {
        ptno cond = Raiz->filho->irmao;
        ptno corpo = Raiz->filho;

        int L_Inicio = Etiqueta++;
        int L_Fim = Etiqueta++;

        printf("L%d\tNADA\n", L_Inicio);
        geracod(cond);
        printf("\tDSVF L%d\n", L_Fim);
        geracod(corpo);
        printf("\tDSVS L%d\n", L_Inicio);
        printf("L%d\tNADA\n", L_Fim);
        return;
    }

    if (Raiz->tipo == NO_NUMERO) { printf("\tCRCT %d\n", Raiz->valor); return; }
    if (Raiz->tipo == NO_VARIAVEL) { printf("\tCRVL %d\n", Raiz->valor); return; }
    if (Raiz->tipo == NO_IDENTIFICADOR) return; 

    if (Raiz->tipo == NO_NEGACAO) {
        geracod(Raiz->filho);
        printf("\tNEGA\n");
        return;
    }

    geracod(Raiz->filho);
    if (Raiz->filho) geracod(Raiz->filho->irmao);

    switch(Raiz->tipo) {
        case NO_SOMA: printf("\tSOMA\n"); break;
        case NO_SUB: printf("\tSUBT\n"); break;
        case NO_MULT: printf("\tMULT\n"); break;
        case NO_DIV: printf("\tDIVI\n"); break;
        case NO_MAIOR: printf("\tCMMA\n"); break;
        case NO_MENOR: printf("\tCMME\n"); break;
        case NO_IGUAL: printf("\tCMIG\n"); break;
    }
}

void geraNos(FILE *f, ptno Raiz) {
    if (!Raiz) return;
    
    if (Raiz->tipo == NO_TIPO_INTEIRO) {
        fprintf(f, "\tn%p [label=\"tipo | inteiro\"]\n", Raiz);
    }
    else if (Raiz->tipo == NO_NUMERO) {
        fprintf(f, "\tn%p [label=\"%s | %d\"]\n", Raiz, nomeNo(Raiz->tipo), Raiz->valor);
    } 
    else if (Raiz->tipo == NO_VARIAVEL) {
        fprintf(f, "\tn%p [label=\"%s | %s\"]\n", Raiz, nomeNo(Raiz->tipo), tabSimb[Raiz->valor].id);
    }
    else if (Raiz->tipo == NO_IDENTIFICADOR) {
        fprintf(f, "\tn%p [label=\"%s | %s\"]\n", Raiz, nomeNo(Raiz->tipo), tabSimb[Raiz->valor].id);
    }
    else if (Raiz->tipo == NO_ID_PROGRAMA) {
        fprintf(f, "\tn%p [label=\"%s | %s\"]\n", Raiz, nomeNo(Raiz->tipo), NomePrograma);
    }
    else {
        fprintf(f, "\tn%p [label=\"%s | \"]\n", Raiz, nomeNo(Raiz->tipo));
    }
    
    geraNos(f, Raiz->filho);
    geraNos(f, Raiz->irmao);
}

void geraLigacoes(FILE *f, ptno Raiz) {
    if (!Raiz) return;
    ptno p = Raiz->filho;
    while(p) {
        fprintf(f, "\tn%p -> n%p\n", Raiz, p);
        p = p->irmao;
    }
    geraLigacoes(f, Raiz->filho);
    geraLigacoes(f, Raiz->irmao);
}

void geraDot(ptno Raiz) {
    FILE *f = fopen("tree.dot", "wt");
    fprintf(f, "digraph {\n");
    fprintf(f, "\tnode [shape=record, height=.1];\n");
    if(Raiz) { geraNos(f, Raiz); geraLigacoes(f, Raiz); }
    fprintf(f, "}\n");
    fclose(f);
}