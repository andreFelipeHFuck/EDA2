all:
	gcc main.c arvores/arvore_b.c -o main
	echo "Arquivos compilados com sucesso"
run:
	./main
clean:
	