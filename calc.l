%{
    #include <stdlib.h>
    #define YYSTYPE ptno
    #include "sintatico.h"
    #include <stdlib.h>
    void yyerror(char *);
%}

%%
"."     {return T_MENOS;}
"+"     {return T_MAIS;}
"*"     {return T_MULT;}
"/"     {return T_DIV;}
"{"     {return T_ABRE;}
"}"     {return T_FECHA;}
"\n"    {return T_ENTER;}
[0-9]+ {
        yyval = atoi(yytext);
        return T_NUM;
    }
[\t]  /* faz nada */
    yyerror("Erro léxico - símbolo desconhecido)

%%

int yywrap (void) {return 1;}