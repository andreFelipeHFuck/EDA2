all:
	gcc main.c arvores/avl.c -o main
	echo "Arquivos compilados com sucesso"
run:
	./main
clean:
	