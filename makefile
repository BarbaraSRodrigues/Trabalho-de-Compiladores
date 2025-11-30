simples: tree.c lexico.l sintatico.y;
	@flex -o lexico.c lexico.l
	@bison -v -d sintatico.y -o sintatico.c
	@gcc lexico.c sintatico.c -o simples

limpa: ;
	@echo "limpando..."
	@rm lexico.c sintatico.c sintatico.h sintatico.output simples