CFLAGS=-O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LIBS=-lm
EXECUTAVEL=EP3

all: $(EXECUTAVEL)

$(EXECUTAVEL): main.o Util.o Arvore.o Fila.o Sugere.o
	gcc main.o Util.o Arvore.o Fila.o Sugere.o $(LIBS) -o $(EXECUTAVEL)

main.o: main.c
	gcc $(CFLAGS) -c main.c

Util.o: Util.c
	gcc $(CFLAGS) -c Util.c

Arvore.o: Arvore.c
	gcc $(CFLAGS) -c Arvore.c

Fila.o: Fila.c
	gcc $(CFLAGS) -c Fila.c

Sugere.o: Sugere.c
	gcc $(CFLAGS) -c Sugere.c

clean: 
	rm -rf *.o $(EXECUTAVEL)

# Para executar com a árvore AVL adicione um '-avl':
# run: $(EXECUTAVEL) 
# 	./$(EXECUTAVEL) -d Dicionario.txt -t TextoEP3.txt -avl
	
run: $(EXECUTAVEL) 
	./$(EXECUTAVEL) -d Portugues.txt -t TextoEP3.txt 

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL) -d Portugues.txt -t TextoEP3.txt 
