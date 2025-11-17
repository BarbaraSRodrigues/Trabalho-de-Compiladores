calc : calc.l calc.y;
	@flex -o lexico.c calc.l
	@bison -v -d calc.y -o sintatico.c
	@gcc sintatico.c -o calc
limpa : ;
	@echo "limpando..."
	@rm lexico.c sintatico.c sintatico.h sintatico.output calc